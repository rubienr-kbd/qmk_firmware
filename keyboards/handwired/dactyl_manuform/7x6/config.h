/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

#define PRODUCT_ID 0x3636
#define DEVICE_VER 0x0002
// 7 rows x 6 columns
#define PRODUCT Dactyl-Manuform (7x6)

// rows are doubled-up
#define MATRIX_ROWS 14
#define MATRIX_COLS  6

// wiring
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROW_PINS       { A3, A2, A1, A0, C15, C14, C13}
#define MATRIX_COL_PINS       { B1, B0, A7, A6, A5, A4 }
#define MATRIX_ROW_PINS_RIGHT { A3, A2, A1, A0, C15, C14, C13}
#define MATRIX_COL_PINS_RIGHT { B1, B0, A7, A6, A5, A4 }

// split keyboard options
#define SERIAL_USART_FULL_DUPLEX    // Enable full duplex operation mode.
#undef  SOFT_SERIAL_PIN             // TODO rubienr - hotfix
                                    //   if full duplex then SOFT_SERIAL_PIN is still defined elsewehre which leads to re-definition of
                                    //   SERIAL_USART_TX_PIN in platforms/chibios/drivers/serial_usart.h:41:
#define SOFT_SERIAL_PIN A9          //
//#define SERIAL_USART_TX_PIN A9    // USART1_TX is PB6 or PA9  see https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html#documentation
#define SERIAL_USART_RX_PIN A10     // USART1_RX is PB7 or PA10 see https://www.st.com/en/microcontrollers-microprocessors/stm32f401.html#documentation
//#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve.
                                    // TODO rubienr:
                                    //   platforms/chibios/drivers/serial_usart.c:245:26: error: 'USART_CR2_SWAP' undeclared (first use in this function); did you mean 'USART_CR2_STOP'?
                                    //   245 |     serial_config.cr2 |= USART_CR2_SWAP;  // master has swapped TX/RX pins

#define SERIAL_USART_DRIVER SD1     // USART driver of TX and RX pin. default: SD1

#define SERIAL_USART_TX_PAL_MODE 7  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7

// boot options: define KC_ESC and KC_F12 as boot-magic buttons
#define BOOTMAGIC_LITE_ROW          0 // see LAYOUT_7x6 in 7x6.h
#define BOOTMAGIC_LITE_COLUMN       0
#define BOOTMAGIC_LITE_ROW_RIGHT    7 // see LAYOUT_7x6 in 7x6.h
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5

// i2c-oled setup
#define OLED_BRIGHTNESS 128
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
#define OLED_DISPLAY_ADDRESS 0x3c

// audio setup
// #define AUDIO_PIN A8
// #define AUDIO_PWM_DRIVER PWMD1
// #define AUDIO_PWM_CHANNEL 1
// #define AUDIO_STATE_TIMER GPTD4
// #define AUDIO_PWM_PAL_MODE 1
// #define AUDIO_CLICKY

// rgb setup
// #define RGB_DI_PIN B2
// #define RGBLED_NUM 2
// #define RGBLED_SPLIT { 2, 2}
// #define RGBLIGHT_SPLIT
// #define RGBLIGHT_LIMIT_VAL 180
// #define RGBLIGHT_MODE_RAINBOW_MOOD 1
// #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
// #define RGBLIGHT_SLEEP
