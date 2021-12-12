#ifdef OLED_ENABLE

#ifdef AUDIO_ENABLE
// sound on clock restart
static float cycle_over_song[][2] = SONG(SCLK_CYCLE_OVER_SONG);
#endif

typedef struct _snakeclock_state_t {
    uint16_t elapsed_seconds;
    uint16_t max_seconds;
    uint16_t x;
    uint16_t prev_x;
    uint16_t y;
    uint16_t prev_y;
    uint64_t last_timer;
    int8_t dx;
    uint8_t px_value : 1;
    uint8_t cpx_value : 1;
    uint8_t prev_cpx_value : 1;
    uint8_t marker_flag : 1;
    uint8_t cycle_unfl : 1;
    uint8_t cycle_ovfl : 1;
    uint8_t display_unfl : 1;
    uint8_t display_ovfl : 1;
    uint8_t clock_direction_increment : 1;
    uint8_t clock_direction_changed : 1;
} snakeclock_state_t;

static snakeclock_state_t _clk_state = {
    .elapsed_seconds=0,
    .max_seconds=SCLK_CLOCK_CYCLE_SECONDS,
    .x=1,
    .prev_x=1,
    .y=1,
    .prev_y=1,
    .last_timer=0,
    .dx=1,
    .px_value=1,
    .cpx_value=0,
    .prev_cpx_value=0,
    .marker_flag=0,
    .cycle_unfl=0,
    .cycle_ovfl=0,
    .display_unfl=0,
    .display_ovfl=0,
    .clock_direction_increment=1,
    .clock_direction_changed=1,};

// off-by-one indexing to stay in the unsigned int range
// x ... OLED_DISPLAY_HEIGHT, y ... OLED_DISPLAY_WIDTH (90° rotated right)
// 0,                         0                    is off display
// 1,                         1                    is top left
// OLED_DISPLAY_HEIGHT,       OLED_DISPLAY_WIDTH   bottom right
// OLED_DISPLAY_HEIGHT+1,     OLED_DISPLAY_WIDTH+1 off display
static void _compute_next_snakeclock_state(snakeclock_state_t* state, bool increment) {
    state->prev_x = state->x;
    state->prev_y = state->y;
    state->prev_cpx_value = state->cpx_value;
    state->cycle_unfl = 0;
    state->cycle_ovfl = 0;
    state->display_unfl = 0;
    state->display_ovfl = 0;
    state->clock_direction_changed = 0;

    // ----- advance clock by one tick

    if (increment) {

        if (state->elapsed_seconds == state->max_seconds - 1) { // time cycle overflow
            state->cycle_ovfl = 1;
            state->elapsed_seconds = 0;
        } else state->elapsed_seconds++;

        if (state->clock_direction_increment == 0) { // clock direction changed
            state->clock_direction_changed = 1;
            state->px_value = (state->px_value == 1) ? 0 : 1;
            state->dx *= -1;
        }

        if (state->dx > 0) { // step right
            if (state->x == OLED_DISPLAY_HEIGHT) {
                state->dx = -1;
                state->y++;

            } else state->x++;
        } else { // step left
            if (state->x == 1) {
                state->dx = 1;
                state->y++;

            } else state->x--;
        }

        state->display_ovfl = (state->y > OLED_DISPLAY_WIDTH) ? 1 : 0;

        if ((state->cycle_ovfl == 1) || (state->display_ovfl == 1) ) {
            state->x = 1;
            state->y = 1;
            state->dx = 1;
            state->px_value = (state->px_value == 1) ? 0 : 1;
        }

    }

    // ----- rewind clock by one tick

    else {
        if (state->elapsed_seconds == 0) { // time cycle underflow
            state->cycle_unfl = 1;
            state->elapsed_seconds = state->max_seconds - 1;
        } else state->elapsed_seconds--;

        if (state->clock_direction_increment == 1) { // clock diection changed
            state->clock_direction_changed = 1;
            state->px_value = (state->px_value == 1) ? 0 : 1;
            state->dx *= -1;
        }

        if (state->dx > 0) { // step right
            if (state->x == OLED_DISPLAY_HEIGHT) {
                state->dx = -1;
                state->y--;

            } else state->x++;
        }
        else { // step left
            if (state->x == 1) {
                state->dx = 1;
                state->y--;

            } else state->x--;
        }

        state->display_unfl = (state->y < 1) ? 1 : 0;


        if (state->cycle_unfl == 1) {
            // on time cycle underflow the whole screen must be re-drawn:
            // reset display, reset clock, then advance clock from 0 until desired time
        } else if ((state->display_unfl == 1)) { // screen underflow
            state->x = OLED_DISPLAY_HEIGHT;
            state->y = OLED_DISPLAY_WIDTH;
            state->dx = (OLED_DISPLAY_WIDTH % 2 == 0) ? -1 : 1;
            state->px_value = (state->px_value == 1) ? 0 : 1;
        }
    }

    state->marker_flag = (state->elapsed_seconds % SCLK_MARKER_DELAY_SECONDS) == 0 ? 1 : 0;
    state->cpx_value = (state->marker_flag == 1) ? !(state->px_value == 1) : (state->px_value == 1);
    state->clock_direction_increment = (increment) ? 1 : 0;

}

static void _render_next_snakeclock_display(const snakeclock_state_t *state) {
    static char counter_buffer[6] = {0};

    oled_write_pixel(state->x - 1, state->y - 1, state->cpx_value);

    uint8_t h = (state->elapsed_seconds / 3600) %10;
    uint8_t m = (state->elapsed_seconds - h * 3600) / 60;
    uint8_t s = (state->elapsed_seconds - h * 3600 - m * 60);
    sprintf(counter_buffer, PSTR("%d%02d%02d"), h, m, s);
    oled_set_cursor(0, oled_max_lines()-1);
    oled_write(counter_buffer, false);
}

static bool _is_render_time(snakeclock_state_t *state) {
    if (timer_elapsed(state->last_timer) >= 1000) {
        state->last_timer = timer_read();
        return true;
    }
    return false;
}

// inverts a pixel every second and moves to next in a snake matter
// leaves one out at every marker
// plays a sound every cycle end
static void render_snakeclock(void) {
    if (!_is_render_time(&_clk_state)) return;
    _compute_next_snakeclock_state(&_clk_state, true);
    _render_next_snakeclock_display(&_clk_state);
#ifdef AUDIO_ENABLE
    if (_clk_state.cycle_ovfl == 1)  PLAY_SONG(cycle_over_song);
#endif
}

static void _reset_snakeclock(void) {
    _clk_state.elapsed_seconds=0;
    _clk_state.x=1;
    _clk_state.prev_x=1;
    _clk_state.y=1;
    _clk_state.prev_y=1;
    _clk_state.last_timer=timer_read();
    _clk_state.dx=1;
    _clk_state.px_value=1;
    _clk_state.cpx_value=0;
    _clk_state.prev_cpx_value=0;
    _clk_state.marker_flag=0;
    _clk_state.cycle_unfl=0;
    _clk_state.cycle_ovfl=0;
    _clk_state.display_unfl=0;
    _clk_state.display_ovfl=0;
    _clk_state.clock_direction_increment=1;
    _clk_state.clock_direction_changed=1;

    if (!is_keyboard_master()) oled_clear();
}

static void _advance_snakeclock(bool forward, uint16_t offset_seconds) {
    // if rewind below counter underflow is requested, redraw from scratch
    if (!forward && offset_seconds> _clk_state.elapsed_seconds) {
        offset_seconds = _clk_state.max_seconds - (offset_seconds - _clk_state.elapsed_seconds);
        forward = true;
        _reset_snakeclock();
    }

    if (forward)
        while (offset_seconds != 0) {
            _compute_next_snakeclock_state(&_clk_state, true);
            if (_clk_state.clock_direction_changed)  oled_write_pixel(_clk_state.prev_x, _clk_state.prev_y, (_clk_state.prev_cpx_value == 1) ? 0 : 1);
            _render_next_snakeclock_display(&_clk_state);
#ifdef AUDIO_ENABLE
            if (_clk_state.cycle_ovfl == 1)  PLAY_SONG(cycle_over_song);
#endif
            offset_seconds--;
    }
    else { // rewind clock
        while (offset_seconds != 0) {
            _compute_next_snakeclock_state(&_clk_state, false);
            if (_clk_state.clock_direction_changed)  oled_write_pixel(_clk_state.prev_x, _clk_state.prev_y, (_clk_state.prev_cpx_value == 1) ? 0 : 1);
            _render_next_snakeclock_display(&_clk_state);
            offset_seconds--;
        }
    }
}

static void snakeclock_rpc_sync_from_master(void) {
    if (m2s_sync_data.data.sync_required == 0) return;

    if (m2s_sync_data.data.audio_on != 0) {
        if (m2s_sync_data.data.audio_on == 1)
            audio_on();
        else if (m2s_sync_data.data.audio_on == 2)
            audio_off();
    }

    if (m2s_sync_data.data.snakeclock_adjust == 1) _advance_snakeclock(true, SCLK_CLOCK_MANUAL_INCREMENT);
    else if (m2s_sync_data.data.snakeclock_adjust == 2) _advance_snakeclock(false, SCLK_CLOCK_MANUAL_INCREMENT);
    else if (m2s_sync_data.data.snakeclock_adjust == 3) _reset_snakeclock();
}
#endif
