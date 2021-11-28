#include QMK_KEYBOARD_H

#include <split_util.h>
#include <keymap_german.h>

#define _QWERTY 0
#define _R_MO   1
#define _L_MO   2

#define R_MO MO(_R_MO)
#define L_MO MO(_L_MO)

enum {
    CT_UE,
    CT_OE,
    CT_AE,
    CT_SS,
    CT_CL,
//  CT_CR,
};

static uint16_t last_timer;
static float tone_qwerty[][2]     = SONG(QWERTY_SOUND);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_7x6(
        KC_ESC  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                          KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        DE_CIRC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    ,                                          KC_7    , KC_8    , KC_9    , KC_0    , DE_PLUS ,
        KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                          KC_Y    ,TD(CT_UE), KC_I    ,TD(CT_OE), KC_P    , KC_BSPC ,
       TD(CT_CL),TD(CT_AE),TD(CT_SS), KC_D    , KC_F    , KC_G    ,                                          KC_H    , KC_J    , KC_K    , KC_L    , DE_HASH ,TD(CT_CL), 
        KC_LCTL , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                                          KC_N    , KC_M    , DE_COMM , DE_DOT  , DE_MINS , KC_LCTL ,
                            KC_LPRN , KC_LBRC ,                                                                                  KC_RBRC , KC_RPRN ,
                                                KC_SPC  , XXXXXXX ,                                          KC_DEL , KC_ENT  ,
                                                                    KC_LALT , L_MO    ,            R_MO    , KC_RCTL,
                                                                    XXXXXXX , XXXXXXX ,            XXXXXXX , DE_ACUT
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
        XXXXXXX , DEBUG   , RGB_VAD , RGB_VAI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        XXXXXXX , AU_TOG  , RGB_SAD , RGB_SAI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
        RESET   , RGB_TOG , RGB_HUD , RGB_HUI , XXXXXXX , XXXXXXX ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
                            RGB_RMOD, RGB_MOD ,                                                                                  _______ , _______ ,
                                                _______ , _______ ,                                          _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______ ,
                                                                    _______ , _______ ,            _______ , _______
    ),
//  [_L_MO] = LAYOUT_7x6(
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                          _______ , _______ , _______ , _______ , _______ , _______ ,
//                          _______ , _______ ,                                                                                  _______ , _______ ,
//                                              _______ , _______ ,                                          _______ , _______ ,
//                                                                  _______ , _______ ,            _______ , _______ ,
//                                                                  _______ , _______ ,            _______ , _______
//  ),
};

// double tap for DE umlauts and ß

// -- ü

void dance_ue_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_U); }
    else { register_code(DE_UDIA); }
}

void dance_ue_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_U); }
    else { unregister_code(DE_UDIA); }
}

// -- ö

void dance_oe_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_O); }
    else { register_code(DE_ODIA); }
}

void dance_oe_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_O); }
    else { unregister_code(DE_ODIA); }
}

// -- caps ä

void dance_ae_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_A); }
    else { register_code(DE_ADIA); }
}

void dance_ae_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_A); }
    else { unregister_code(DE_ADIA); }
}

// -- ß

void dance_ss_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_S); }
    else { register_code(DE_SS); }
}

void dance_ss_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_S); }
    else { unregister_code(DE_SS); }
}

// -- caps lock

void dance_cl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_LSFT); }
    else { register_code(KC_CAPS); }
}

void dance_cl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_LSFT); }
    else { unregister_code(KC_CAPS); }
}

//void dance_cr_finished(qk_tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) { register_code16(KC_RSFT); }
//    else { register_code(KC_CAPS); }
//}
//
//void dance_cr_reset(qk_tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {  unregister_code16(KC_RSFT); }
//    else { unregister_code(KC_CAPS); }
//}
  
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_UE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ue_finished, dance_ue_reset),
    [CT_OE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_oe_finished, dance_oe_reset),
    [CT_AE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ae_finished, dance_ae_reset),
    [CT_SS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ss_finished, dance_ss_reset),
    [CT_CL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cl_finished, dance_cl_reset),
//  [CT_CR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cr_finished, dance_cr_reset),
};

// init section

void board_init(void) {
#ifdef OLED_ENABLE
    // B9 is configured as I2C1_SDA in the board file; that function must be disabled before using B7 as I2C1_SDA.
    // https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/onekey/blackpill_f401/blackpill_f401.c
    // https://github.com/qmk/qmk_firmware/pull/10322
    setPinInputHigh(B9);
#endif
}

// display section

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
