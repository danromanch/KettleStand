#include "lib/common/struct.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "lib/common/pins.h"
#include "utils/log.h"
#include "lib/common/error.h"
#include "storage/storage.h"
#include "states/sensorState.h"

esp_err_t turnOnKettle(void)
{
    state_sensor_t state = sensorRead();
    block_limit_t limits = {0};
    storage_load(STORAGE_LIMIT, &limits, sizeof(limits)); 
    if (state.waterLevel <= limits.minWater)
    {
        LOG("Kettle was tried to be started, but couldn`t because water level is equal = %d", state.waterLevel);
        return APP_ERR_NO_WATER;
    }
    if (state.temperature >= limits.maxTemp) 
    {
        LOG("Kettle was tried to be started, but couldn`t because temperature is equal = %.2f", state.temperature);
        return APP_ERR_OVER_TEMP;
    }
    LOG("Kettle turned on");
    gpio_set_level(RLY_PIN, 1);
    return ESP_OK;
}

void turnOffKettle(void)
{
    LOG("Kettle turned off");
    gpio_set_level(RLY_PIN, 0);
    return;
}