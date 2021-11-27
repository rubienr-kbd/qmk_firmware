#pragma once

#include_next <mcuconf.h>

// split keyboard
#undef  STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

// i2c periphery
#undef  STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
#define STM32_I2C_USE_DMA  TRUE

// audio
// #undef  STM32_PWM_USE_TIM1
// #define STM32_PWM_USE_TIM1 TRUE
// #undef  STM32_GPT_USE_TIM4
// #define STM32_GPT_USE_TIM4 TRUE
