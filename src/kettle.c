// This file is responsible for kettle control
#include "common/struct.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "pins.h"
#include "log.h"
#include <stdint.h>
#include "sensors/temperature.h"
#include "sensors/waterLevel.h"
#include "common/error.h"
#include "storage/storage.h"

esp_err_t turnOnKettle(void)
{
    updateTemperature();
    updateWaterLevel();
    uint8_t temperature = getTemperature();
    uint8_t waterLevel = getWaterLevel();
    block_limit_t limits = {0};
    storage_load(STORAGE_LIMIT, &limits, sizeof(limits)); 
    if (waterLevel <= limits.minWater)
    {
        logMessage("Kettle was tried to be started at ,but couldnt because water level is equal =");
        return APP_ERR_NO_WATER;
    }
    if (temperature >= limits.maxTemp) 
    {
        logMessage("Kettle was tried to be started at ,but couldnt because temperature is equal =");
        return APP_ERR_OVER_TEMP;
    }
    logMessage("Kettle turned on at");
    gpio_set_level(RLY_PIN, 1);
    return ESP_OK;
}

void turnOffKettle(void)
{
    logMessage("Kettle turned off at");
    gpio_set_level(RLY_PIN, 0);
    return;
}