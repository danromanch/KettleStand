#include "driver/i2c_master.h"
#include "hal/i2c_types.h"
#include "lib/common/pins.h"
#include "soc/clk_tree_defs.h"
#include "stdbool.h"
#include "utils/log.h"

#define I2C_FREQ_HZ 100000

static i2c_master_bus_handle_t s_bus_handle = NULL;
static i2c_master_dev_handle_t s_oled_dev = NULL;
static i2c_master_dev_handle_t s_temp_dev = NULL;

void configI2C(void)
{
    i2c_master_bus_config_t bus_cfg = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = I2C_SCL_PIN,
        .sda_io_num = I2C_SDA_PIN,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_new_master_bus(&bus_cfg, &s_bus_handle);

    i2c_device_config_t oled_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = OLED_ADRESS,
            .scl_speed_hz = I2C_FREQ_HZ,
    };
    i2c_master_bus_add_device(s_bus_handle, &oled_cfg, &s_oled_dev);

    i2c_device_config_t temp_cfg = {
            .dev_addr_length = I2C_ADDR_BIT_LEN_7,
            .device_address = TEMP_ADRESS,
            .scl_speed_hz = I2C_FREQ_HZ,
    };
    i2c_master_bus_add_device(s_bus_handle, &temp_cfg, &s_temp_dev);

    LOG("I2C initialized");
}