#include QMK_KEYBOARD_H
#include <split_util.h>
#include <keymap_german.h>

#define _QWERTY 0
#define _R_MO   1
#define _L_MO   2

#define R_MO MO(_R_MO)
#define L_MO MO(_L_MO)

#include "oled.c"
#include "input.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {                            
    [_QWERTY] = LAYOUT_7x6(                                                               
        KC_ESC  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                            KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  ,
        DE_CIRC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                                            KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , DE_PLUS ,
        KC_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                                            KC_Z    , KC_U    , KC_I    , KC_O    , KC_P    , KC_DEL  ,
       TD(TD_CL), KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                                            KC_H    , KC_J    , KC_K    , KC_L    , DE_HASH ,TD(TD_CR), 
        KC_LCTL , KC_Y    , KC_X    , KC_C    , KC_V    , KC_B    ,                                            KC_N    , KC_M    , DE_COMM , DE_DOT  , DE_MINS , KC_RCTL ,
                            KC_LBRC , KC_LPRN ,                                                                                    KC_RPRN , KC_RBRC , 
                                                KC_SPC  , KC_TAB  ,                                            KC_BSPC , KC_ENT  ,
                                                                    KC_LALT , L_MO    ,    R_MO    , KC_RALT ,
                                                                    CK_UCIS , XXXXXXX ,    XXXXXXX , DE_ACUT
    ),                                                                                    
    [_R_MO] = LAYOUT_7x6(                                                                 
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            RESET   , KC_INS  , KC_HOME , KC_PGUP , KC_F11  , KC_F12  ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            XXXXXXX , KC_DEL  , KC_END  , KC_PGDN , XXXXXXX , XXXXXXX ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            XXXXXXX , XXXXXXX , KC_UP   , XXXXXXX , XXXXXXX , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            XXXXXXX , KC_LEFT , KC_DOWN , KC_RGHT , XXXXXXX , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
                            _______ , _______ ,                                                                                    XXXXXXX , XXXXXXX ,
                                                _______ , _______ ,                                            _______ , _______ ,
                                                                    _______ , _______ ,    _______ , _______ ,
                                                                    _______ , _______ ,    _______ , _______
    ),                                                                                    
    [_L_MO] = LAYOUT_7x6(                                                                 
        TERM_OFF, TERM_ON , XXXXXXX , XXXXXXX , XXXXXXX , RESET   ,                                            _______ , KC_PSCR , KC_SLCK , KC_PAUS , _______ , _______ , 
        DEBUG   , XXXXXXX , RGB_SPD , RGB_SPI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , XXXXXXX , RGB_VAD , RGB_VAI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , AU_TOG  , RGB_SAD , RGB_SAI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , RGB_TOG , RGB_HUD , RGB_HUI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
                            RGB_RMOD, RGB_MOD ,                                                                                    _______ , _______ ,
                                                _______ , _______ ,                                            _______ , _______ ,
                                                                    _______ , _______ ,    _______ , _______ ,
                                                                    _______ , _______ ,    _______ , _______
    ),                                                                                    
//  [_UNI] = LAYOUT_7x6(                                                                  
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//                          XXXXXXX , XXXXXXX ,                                                                                    XXXXXXX , XXXXXXX ,
//                                              _______ , _______ ,                                            _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______
//  ),                                                                                    
//  [_L_MO] = LAYOUT_7x6(                                                                 
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
//      _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
//                          _______ , _______ ,                                                                                    _______ , _______ ,
//                                              _______ , _______ ,                                            _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______
//  ),
};


void board_init(void) {
#ifdef OLED_ENABLE
    // B9 is configured as I2C1_SDA in the board file; that function must be disabled before using B7 as I2C1_SDA.
    // https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/onekey/blackpill_f401/blackpill_f401.c
    // https://github.com/qmk/qmk_firmware/pull/10322
    setPinInputHigh(B9);
#endif
}


