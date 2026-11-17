#include "common/struct.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "common/pins.h"
#include "utils/log.h"
#include <stdint.h>
#include "sensors/temperature.h"
#include "sensors/waterLevel.h"
#include "common/error.h"
#include "storage/storage.h"

esp_err_t turnOnKettle(void)
{
    updateTemperature();
    updateWaterLevel();
    float temperature = getTemperature();
    uint8_t waterLevel = getWaterLevel();
    block_limit_t limits = {0};
    storage_load(STORAGE_LIMIT, &limits, sizeof(limits)); 
    if (waterLevel <= limits.minWater)
    {
        LOG("Kettle was tried to be started, but couldn`t because water level is equal = %d", waterLevel);
        return APP_ERR_NO_WATER;
    }
    if (temperature >= limits.maxTemp) 
    {
        LOG("Kettle was tried to be started, but couldn`t because temperature is equal = %.2f", temperature);
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