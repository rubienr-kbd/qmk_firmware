#ifdef OLED_ENABLE

static uint16_t last_timer;
static float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

// inverts a pixel every second and moves to next,
// leaves one out every 15 minutes,
// beeps every hour and starts from first pixel
static void render_sandclock(void) {
    static int x = 0, y = 0, dx=1;
    static bool px_value = true;
    static uint16_t elapsed_seconds = 0;

    if (timer_elapsed(last_timer) < 1000) return;
    last_timer = timer_read();
    elapsed_seconds++;

    // render pixels, every 15 minutes leave one out 
    oled_write_pixel(x,y, (0 == (elapsed_seconds % (60 * 15))) ? !px_value : px_value);
    x += dx;

    // every hour: play a notification, restart from top
    if (elapsed_seconds > (60*60)) {
      x = 0;
      y = 0;
      dx = 1;
      px_value = !px_value;
      elapsed_seconds = 0;
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      return;
    }

    // advance pixel location
    if (x >= OLED_DISPLAY_HEIGHT || x < 0) {
        dx *= -1;
        y++;
        
        if (y >= OLED_DISPLAY_WIDTH) {
          y = 0;
          px_value = !px_value;
        }
    }
}

#endif

