#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "lib/common/struct.h"
#include "sensors/temperature.h"
#include "sensors/waterLevel.h"
#include <stdint.h>

SemaphoreHandle_t sensorsMutex;
static state_sensor_t s_latest_state = {0};

void sensorsStateInit(void)
{
    sensorsMutex = xSemaphoreCreateMutex();
}

void sensorUpdate(void)
{
    updateTemperature();
    updateWaterLevel();
    float temp = getTemperature();
    uint8_t level = getWaterLevel();
    if (xSemaphoreTake(sensorsMutex, pdMS_TO_TICKS(50)) == pdTRUE)
    {
        s_latest_state.temperature = temp;
        s_latest_state.waterLevel = level;
        xSemaphoreGive(sensorsMutex);
    }
}

state_sensor_t sensorRead(void)
{
    state_sensor_t copy = {0};
    if (xSemaphoreTake(sensorsMutex, pdMS_TO_TICKS(50)) == pdTRUE)
    {
        copy = s_latest_state;
        xSemaphoreGive(sensorsMutex);
    }
    return copy;
}