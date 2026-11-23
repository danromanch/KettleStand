#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui/button.h"
#include "kettle.h"

void kettleTask(void* pointer)
{
    TickType_t last_wake_time = xTaskGetTickCount();
    const TickType_t poll_period = pdMS_TO_TICKS(200);
    
    while (1) {
        if (buttonState)
        {
            turnOnKettle();
        } 
        else
        {
            turnOffKettle();
        }
        vTaskDelayUntil(&last_wake_time, poll_period);
    }
}