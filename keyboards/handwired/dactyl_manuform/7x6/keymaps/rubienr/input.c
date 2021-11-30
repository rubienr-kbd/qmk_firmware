// combo input

enum combo_events {
  CB_UE,
  CB_OE,
  CB_AE,
  CB_SZ,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Z, COMBO_END};
combo_t key_combos[] = {
    COMBO(ae_combo, DE_ADIA),
    COMBO(oe_combo, DE_ODIA),
    COMBO(ue_combo, DE_UDIA),
    COMBO(sz_combo, DE_SS),
};


// custom key codes

enum custom_keycodes_t {
   CK_UCIS = SAFE_RANGE,
};

// utf8 ucis input
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop"        , 0x1F4A9),                // 💩
    UCIS_SYM("rofl"        , 0x1F923),                // 🤣
    UCIS_SYM("cuba"        , 0x1F1E8, 0x1F1FA),       // 🇨🇺
    UCIS_SYM("look"        , 0x0CA0, 0x005F, 0x0CA0), // ಠ_ಠ
    UCIS_SYM("extrakurz"   , 0x0306),                 // ​˘
    UCIS_SYM("doppelpunkt" , 0x02D0),                 //​ ː​
    UCIS_SYM("shrug"       , 0x00af, 0x005c, 0x005f, 0x0028, 0x30c4, 0x0029, 0x005f, 0x002f, 0x00af) // ¯\_(ツ)_/¯
);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CK_UCIS:
        if (!record->event.pressed) qk_ucis_start();
        break;
    }
    return true;
}

// tap dance input / double tap input

enum {
    TD_CL,
    TD_CR,
};

void dance_cl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_LSFT); }
    else {register_code(KC_CAPS); }
} 

void dance_cl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_LSFT); }
    else { unregister_code(KC_CAPS); }
}

void dance_cr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_RSFT); }
    else { register_code(KC_CAPS); }
}

void dance_cr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_RSFT); }
    else { unregister_code(KC_CAPS); }
}
  
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cl_finished, dance_cl_reset),
    [TD_CR]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_cr_finished, dance_cr_reset),
};
