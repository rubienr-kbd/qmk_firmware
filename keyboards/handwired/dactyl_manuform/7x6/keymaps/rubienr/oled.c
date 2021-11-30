#include "sandclock.c"

#ifdef OLED_ENABLE

static void render_master_status(void) {
    // layer info
    oled_write_P(PSTR("L:"), false);
    static char rgb_buffer[10];

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWE"), false);
            break;
        case _R_MO:
            oled_write_P(PSTR("RMO"), false);
            break;
        case _L_MO:
            oled_write_P(PSTR("LMO"), false);
            break;
        default:
            oled_write_P(PSTR("nil"), false);
    }
    
    // kbd LED states
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), led_state.scroll_lock);

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

