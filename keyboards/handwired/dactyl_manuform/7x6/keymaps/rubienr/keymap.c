#include QMK_KEYBOARD_H

#include <split_util.h>

#define _QWERTY 0
#define _R_MO   1
#define _L_MO   2

#define R_MO MO(_R_MO)
#define L_MO MO(_L_MO)

static uint16_t last_timer;
static float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_7x6(
        KC_ESC  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                          KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        KC_CIRC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    ,                                          KC_7    , KC_8    , KC_9    , KC_0    , KC_BSPC ,
        KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                          KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
        KC_LSFT , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                          KC_H    , KC_J    , KC_K    , KC_L    , XXXXXXX , XXXXXXX ,
        KC_LCTL , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                                          KC_N    , KC_M    , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
                            KC_LPRN , KC_LBRC ,                                                                                  KC_RBRC , KC_RPRN ,
                                                KC_LALT , KC_SPC  ,                                          KC_ENT  , KC_RCTL ,
                                                                    KC_DEL  , L_MO    ,            R_MO    , KC_DEL  ,
                                                                    XXXXXXX , XXXXXXX ,            XXXXXXX , XXXXXXX
    ),

    [_R_MO] = LAYOUT_7x6(
        TERM_OFF, TERM_ON , _______ , _______ , _______ , _______ ,                                          XXXXXXX , KC_PSCR , KC_SLCK , KC_PAUS , KC_F11  , KC_F12  ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                          XXXXXXX , KC_INS  , KC_HOME , KC_PGUP , XXXXXXX , XXXXXXX ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                          XXXXXXX , KC_DEL  , KC_END  , KC_PGDN , XXXXXXX , XXXXXXX ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                          XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX , XXXXXXX ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                          XXXXXXX , KC_LEFT , KC_DOWN , KC_RIGHT, XXXXXXX , RESET   ,
                            _______ , _______ ,                                                                                  XXXXXXX , XXXXXXX ,
                                                _______ , _______ ,                                          _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______
    ),

    [_L_MO] = LAYOUT_7x6(
        TERM_OFF, TERM_ON , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        XXXXXXX , XXXXXXX , RGB_SPD , RGB_SPI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        XXXXXXX , XXXXXXX , RGB_VAD , RGB_VAI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        XXXXXXX , XXXXXXX , RGB_SAD , RGB_SAI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        RESET   , RGB_TOG , RGB_HUD , RGB_HUI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
                            RGB_RMOD, RGB_MOD,                                                                                  _______ , _______ ,
                                                _______ , _______ ,                                          _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______
    ),
//    [_L_MO] = LAYOUT_7x6(
//        _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//        _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//        _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//        _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//        _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//                            _______ , _______ ,                                                                                  _______ , _______ ,
//                                                _______ , _______ ,                                          _______ , _______ ,
//                                                                    _______ , _______ ,            _______ , _______ ,
//                                                                    _______ , _______ ,            _______ , _______
//    ),
};

void board_init(void) {
#ifdef OLED_ENABLE
    // B9 is configured as I2C1_SDA in the board file; that function must be disabled before using B7 as I2C1_SDA.
    // https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/onekey/blackpill_f401/blackpill_f401.c
    // https://github.com/qmk/qmk_firmware/pull/10322
    setPinInputHigh(B9);
#endif
}

#ifdef OLED_ENABLE

static void render_master_status(void) {

    if (is_keyboard_master()) {
        oled_write_P(PSTR("Mastr"), false);
    }

    // layer info
    oled_write_P(PSTR("\nL:"), false);
    static char rgb_buffer[10];

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWE\n"), false);
            break;
        case _R_MO:
            oled_write_P(PSTR("RMO\n"), false);
            break;
        case _L_MO:
            oled_write_P(PSTR("LMO\n"), false);
            break;
        default:
            oled_write_P(PSTR("nil\n"), false);
    }
    
    // kbd LED states
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("NUM\n"), led_state.num_lock);
    oled_write_P(PSTR("CAP\n"), led_state.caps_lock);
    oled_write_P(PSTR("SCR\n"), led_state.scroll_lock);

    // RGB info
    sprintf(rgb_buffer, PSTR("RGB%02d"), rgblight_get_mode());
    oled_write(rgb_buffer, rgblight_is_enabled());
    sprintf(rgb_buffer, PSTR("H:%03d"), rgblight_get_hue());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("S:%03d"), rgblight_get_sat());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("V:%03d"), rgblight_get_val());
    oled_write(rgb_buffer, false);
    sprintf(rgb_buffer, PSTR("s:%03d"), rgblight_get_speed());
    oled_write(rgb_buffer, false);
}

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

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    rotation = OLED_ROTATION_270;
    last_timer = timer_read();
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) render_master_status();
    else render_sandclock();
}

#endif
