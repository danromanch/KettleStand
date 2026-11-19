#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "states/sensorState.h"

void sensorTask(void* pointer)
{
    TickType_t last_wake_time = xTaskGetTickCount();
    const TickType_t poll_period = pdMS_TO_TICKS(200);
    
    while (1)
    {
        sensorUpdate();
        vTaskDelayUntil(&last_wake_time, poll_period);
    }
}

