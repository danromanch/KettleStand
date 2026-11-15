// This file is responsible for kettle control
#include "driver/gpio.h"
#include "pins.h"
#include "log.h"
#include <stdint.h>

uint8_t turnOnKettle(void)
{
    if (waterLevel <= MIN_WTR_CONST)
    {
        logMessage("Kettle was tried to be started at ,but couldnt because water level is equal =");
        return 1;
    }
    if (temperature >=MAX_TEMP_CONST)
    {
        logMessage("Kettle was tried to be started at ,but couldnt because temperature is equal =");
        return 2;
    }
    logMessage("Kettle turned on at");
    gpio_set_level(RLY_PIN, 1);
    return 0;
}

void turnOffKettle(void)
{
    logMessage("Kettle turned off at");
    gpio_set_level(RLY_PIN, 0);
    return;
}