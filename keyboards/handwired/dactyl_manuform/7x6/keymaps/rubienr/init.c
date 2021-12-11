#ifdef OLED_ENABLE
#include <transactions.h>
static void snakeclock_rpc_sync_from_master(void);

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be disabled before using B7 as I2C1_SDA.
    // https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/onekey/blackpill_f401/blackpill_f401.c
    // https://github.com/qmk/qmk_firmware/pull/10322
    setPinInputHigh(B9);
}

typedef struct {
    uint8_t sync_required : 1;     // 0 noop
    uint8_t audio_on : 2;          // 0 noop, 1 enable,    2 disable
    uint8_t snakeclock_adjust : 2; // 0 noop, 1 increment, 2 decrement, 3 reset
} m2s_sync_t;

typedef union {
    m2s_sync_t data;
    uint8_t raw;
} m2s_sync_ut;

static m2s_sync_ut m2s_sync_data = {.data.sync_required = 0, .data.audio_on=0, .data.snakeclock_adjust=0};

void user_sync_sclk_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    m2s_sync_data = *(const m2s_sync_ut*)in_data;
    snakeclock_rpc_sync_from_master();
    m2s_sync_data.raw = 0;
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_SCLK, user_sync_sclk_slave_handler);
}

#endif