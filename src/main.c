#include "esp_err.h"
#include "esp_log.h"
#include "kettle.h"
#include "config.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "storage/storage.h"
#include "tasks/sensorTask.h"
#include "states/sensorState.h"

TaskHandle_t sensorHandler;

void app_main(void)
{
    
    ESP_LOGI("MAIN", "Serial monitor active");
    ESP_ERROR_CHECK(storage_init());
    configPins();
    //configI2C();
    sensorsStateInit();
    xTaskCreate(sensorTask, "SENSOR_UPDATE", 4096, NULL, 1, &sensorHandler);
    turnOnKettle();
}

