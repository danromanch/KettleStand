#include "esp_log.h"
#include "storage/storage.h"
#include "config.h"
#include "states/sensorState.h"

void configMain(void)
{
    ESP_LOGI("MAIN", "Serial monitor active");
    ESP_ERROR_CHECK(storage_init());
    configPins();
    configISR();
    //configI2C();
    sensorsStateInit();
    configTask();
}