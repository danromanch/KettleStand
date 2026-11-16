#include "esp_err.h"
#include "kettle.h"
#include "config.h"
#include "storage/storage.h"

void app_main(void)
{
    ESP_ERROR_CHECK(storage_init());
    configPins();
    configI2C();
    turnOnKettle();
}
