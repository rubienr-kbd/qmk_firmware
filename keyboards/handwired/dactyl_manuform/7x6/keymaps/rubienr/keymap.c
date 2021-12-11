#include QMK_KEYBOARD_H
#include <split_util.h>
#include <keymap_german.h>

#define _QWERTY    0
#define _TG_1      1
#define _MO_1      2

#define MO_1 MO(_MO_1)
#define TG_1 TG(_TG_1)

#include "init.c"
#include "input.c"
#include "oled.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {                            
    [_QWERTY] = LAYOUT_7x6(                                                               
        KC_ESC  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   ,                                            KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , DE_SS   ,
        DE_CIRC , DE_1    , DE_2    , DE_3    , DE_4    , DE_5    ,                                            DE_6    , DE_7    , DE_8    , DE_9    , DE_0    , DE_ACUT ,
        KC_TAB  , DE_Q    , DE_W    , DE_E    , DE_R    , DE_T    ,                                            DE_Z    , DE_U    , DE_I    , DE_O    , DE_P    , DE_PLUS ,
       TD(TD_CL), DE_A    , DE_S    , DE_D    , DE_F    , DE_G    ,                                            DE_H    , DE_J    , DE_K    , DE_L    , DE_HASH ,TD(TD_CR),
       KC_LCTL  , DE_Y    , DE_X    , DE_C    , DE_V    , DE_B    ,                                            DE_N    , DE_M    , DE_COMM , DE_DOT  , DE_MINS , KC_RCTL ,
                            DE_LABK ,TD(TD_TG_L),                                                                                 TD(TD_TG_R), KC_DEL  ,
                                                KC_SPC  , KC_TAB  ,                                            KC_BSPC , KC_ENT  ,
                                                                       MO_1 , XXXXXXX ,    KC_LEFT , KC_UP ,
                                                                    XXXXXXX , CK_UCIS ,    KC_DOWN , KC_RGHT
    ),
    [_TG_1] = LAYOUT_7x6(                                                                 
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
                            _______ , _______ ,                                                                                    _______ , _______ ,
                                                _______ , _______ ,                                            _______ , _______ ,
                                                                    _______ , _______ ,    KC_HOME , KC_PGUP ,
                                                                    _______ , _______ ,    KC_PGDN , KC_END
    ),
    [_MO_1] = LAYOUT_7x6(                                                                 
        TERM_OFF, TERM_ON , XXXXXXX , XXXXXXX , XXXXXXX , CK_TIMI ,                                            _______ , KC_PSCR , KC_SLCK , KC_PAUS , _______ , KC_F12  ,
        DEBUG   , XXXXXXX , RGB_SPD , RGB_SPI , XXXXXXX , CK_TIMR ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , XXXXXXX , RGB_VAD , RGB_VAI , XXXXXXX , CK_TIMD ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , AU_TOG  , RGB_SAD , RGB_SAI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , RGB_TOG , RGB_HUD , RGB_HUI , XXXXXXX , XXXXXXX ,                                            _______ , _______ , _______ , _______ , _______ , _______ ,
                            RGB_RMOD, RGB_MOD ,                                                                                    _______ , _______ ,
                                                _______ , _______ ,                                            _______ , _______ ,
                                                                    _______ , _______ ,    _______ , _______ ,
                                                                    _______ , RESET   ,      RESET , _______
    ),
//  [_L_DSBL] = LAYOUT_7x6(                                                                  
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                            XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
//                          XXXXXXX , XXXXXXX ,                                                                                    XXXXXXX , XXXXXXX ,
//                                              _______ , _______ ,                                            _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______ ,
//                                                                  _______ , _______ ,    _______ , _______
//  ),                                                                                 
//  [_L_TRNS] = LAYOUT_7x6(                                                                 
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
