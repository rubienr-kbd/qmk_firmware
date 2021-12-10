#include "sandclock.c"

#ifdef OLED_ENABLE

static void render_master_status(void) {
    // layer info
    
    static char rgb_buffer[10];

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
        case _TG_1:
            oled_write_P(PSTR("L:QWE"), false);
            break;
        case _MO_1:
            oled_write_P(PSTR("L"), true);
            oled_write_P(PSTR(":MO "), false);
            break;
        default:
            oled_write_P(PSTR("L:nil"), false);
    }
    
    // kbd LED states
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    oled_write_P(PSTR("A"), audio_is_on());
    oled_write_P(PSTR(" "), false);

    // RGB info
    sprintf(rgb_buffer, PSTR("RGB%02d"), rgblight_get_mode());
    oled_write(rgb_buffer, rgblight_is_enabled());
    sprintf(rgb_buffer, PSTR("H %03d"), rgblight_get_hue());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("S %03d"), rgblight_get_sat());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("V %03d"), rgblight_get_val());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("s %3d"), rgblight_get_speed());
    oled_write(rgb_buffer, false);
    oled_write_ln(PSTR(""), false);

    oled_write_P(PSTR("M:"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("<^>"), false);
            break;
        case _TG_1:
            oled_write_P(PSTR("PGE"), false);
            break;
        default:
            oled_write_P(PSTR("nil"), false);
    }

        
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    rotation = OLED_ROTATION_270;
    last_timer = timer_read();
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) render_master_status();
    else {
#ifdef OLED_ENABLE
      render_sandclock();
#endif
    }
}

#endif

