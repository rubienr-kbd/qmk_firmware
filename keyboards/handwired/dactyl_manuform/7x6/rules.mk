# qmk flash -kb handwired/dactyl_manuform/7x6 -km rubienr

# MCU name
MCU = STM32F401

# bootloader selection
BOOTLOADER       = stm32-dfu
BOOTMAGIC_ENABLE = lite       # enable Bootmagic Lite

SPLIT_KEYBOARD = yes
SERIAL_DRIVER  = usart

OLED_ENABLE = yes
OLED_DRIVER = SSD1306         # for SSD1306 or SH1106

MOUSEKEY_ENABLE = no          # mouse keys
EXTRAKEY_ENABLE = no          # audio control and system control

# terminal and debug
TERMINAL_ENABLE = yes         # command-line-like interface thorugh a text ditor
CONSOLE_ENABLE  = yes         # console for debug - qmk console -l
COMMAND_ENABLE  = no          # commands for debug and configuration (formerly known as Magic)

# Do not enable SLEEP_LED_ENABLE. It uses the same timer as BACKLIGHT_ENABLE.
SLEEP_LED_ENABLE = no         # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no              # USB Nkey Rollover

# BACKLIGHT_ENABLE = no       # enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes         # enable keyboard RGB underglow
RGBLIGHT_DRIVER = WS2812

AUDIO_ENABLE = yes            # audio output
AUDIO_DRIVER = pwm_hardware

# for umlaut and caps lock
TAP_DANCE_ENABLE = yes        # cl
COMBO_ENABLE     = yes        # umlaut

# unicode and special characters. only one at the same time: UNICODE, UNICODEMAP, UCIS
#UNICODE_ENABLE    = no        # https://docs.qmk.fm/#/feature_unicode?id=basic-unicode
#UNICODEMAP_ENABLE = no        # https://docs.qmk.fm/#/feature_unicode?id=unicode-map
UCIS_ENABLE       = yes       # https://docs.qmk.fm/#/feature_unicode?id=ucis
