#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tasks/kettleTask.h"
#include "tasks/sensorTask.h"

TaskHandle_t sensorHandler;
TaskHandle_t kettleHandler;

void configTask(void)
{
    xTaskCreate(sensorTask, "SENSOR_UPDATE", 4096, NULL, 1, &sensorHandler);
    xTaskCreate(kettleTask, "KETTLE_CONTROL", 8192, NULL, 0, &kettleHandler);
}