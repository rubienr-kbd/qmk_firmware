# qmk flash -kb handwired/dactyl_manuform/7x6 -km rubienr

# MCU name
MCU = STM32F401

# bootloader selection
BOOTLOADER = stm32-dfu

BOOTMAGIC_ENABLE = lite      # Enable Bootmagic Lite

# MOUSEKEY_ENABLE = yes      # Mouse keys
# EXTRAKEY_ENABLE = yes      # Audio control and System control

CONSOLE_ENABLE = yes          # Console for debug
COMMAND_ENABLE = yes          # Commands for debug and configuration

# Do not enable SLEEP_LED_ENABLE. It uses the same timer as BACKLIGHT_ENABLE.
SLEEP_LED_ENABLE = no         # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no              # USB Nkey Rollover

# BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
# RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
# RGBLIGHT_DRIVER = WS2812
# AUDIO_ENABLE = yes          # Audio output
# AUDIO_DRIVER = pwm_hardware

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

OLED_ENABLE = yes
OLED_DRIVER = SSD1306         # for SSD1306 or SH1106
