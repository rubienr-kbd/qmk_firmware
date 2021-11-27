#include QMK_KEYBOARD_H

#include <split_util.h>

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_7x6(
        KC_ESC,  KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                           KC_F6 , KC_F7 , KC_F8   , KC_F9  , KC_F10  , KC_F11    ,
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                           KC_6  , KC_7  , KC_8    , KC_9   , KC_0    , KC_BSPC   ,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                           KC_Y  , KC_U  , KC_I    , KC_O   , KC_P    , KC_MINS   ,
        KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  ,                           KC_H  , KC_J  , KC_K    , KC_L   , KC_SCLN , KC_QUOT   ,
        KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                           KC_N  , KC_M  , KC_COMM , KC_DOT , KC_SLSH , KC_BSLASH ,
                         KC_LBRC,KC_RBRC,                                                          KC_PLUS , KC_EQL ,
                                         RAISE,  KC_SPC,                           KC_ENT, LOWER,
                                                 KC_TAB,KC_HOME,          KC_END,  KC_DEL,
                                                 KC_BSPC, KC_GRV,         KC_LGUI, KC_LALT
    ),

    [_LOWER] = LAYOUT_7x6(
        KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6  ,                         KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 ,
        KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                                                _______,KC_PSCR,            _______, KC_P0,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______,
                                                _______,_______,            _______,_______
    ),

    [_RAISE] = LAYOUT_7x6(
        KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
        _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
        _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,
                                                _______,_______,            KC_EQL ,_______,
                                                _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______
    )
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

void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QERTY\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}


static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }

    return rotation;
}

void oled_task_user(void) {
    if (!is_keyboard_left()) {
        render_status();     // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();       // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }
}

#endif
