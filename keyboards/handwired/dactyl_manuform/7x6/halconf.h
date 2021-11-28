#pragma once

// split keyboard
#define HAL_USE_SERIAL TRUE
#define SERIAL_USB_BUFFERS_SIZE 256

// i2c periphery
#define HAL_USE_I2C TRUE

// audio
#define HAL_USE_PWM TRUE
#define HAL_USE_PAL TRUE
#define HAL_USE_GPT TRUE

#include_next <halconf.h>
