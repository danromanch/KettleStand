#include "esp_err.h"
#include "esp_log.h"
#include "kettle.h"
#include "config.h"
#include "storage/storage.h"
static const char *TAG = "MAIN";

void app_main(void)
{
    ESP_LOGI(TAG, "Serial monitor active");
    ESP_ERROR_CHECK(storage_init());
    configPins();
    //configI2C();
    turnOnKettle();
}
