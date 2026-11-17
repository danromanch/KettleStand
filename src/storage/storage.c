#include "storage.h"
#include <string.h>
#include "esp_err.h"
#include "utils/log.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "common/struct.h"

esp_err_t storage_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK) return ret;
    block_limit_t limit = {.maxTemp=100.0, .minWater=5};
    block_calib_t calib = {.loadCellScale=0};
    block_network_t network = {.ssid="0", .password="0"};
    if (storage_load(STORAGE_LIMIT, &limit, sizeof(limit)) != ESP_OK) {
        ESP_ERROR_CHECK(storage_save(STORAGE_LIMIT, &limit, sizeof(limit)));
    }
    if (storage_load(STORAGE_CALIBR, &calib, sizeof(calib)) != ESP_OK) {
        ESP_ERROR_CHECK(storage_save(STORAGE_CALIBR, &calib, sizeof(calib)));
    }
    if (storage_load(STORAGE_NETWORK, &network, sizeof(network)) != ESP_OK) {
        ESP_ERROR_CHECK(storage_save(STORAGE_NETWORK, &network, sizeof(network)));
    }
    LOG("Storage initialized");
    return ESP_OK;
}

esp_err_t storage_save(const char *key, const void *data, size_t size) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NS, NVS_READWRITE, &handle);
    if (err != ESP_OK) return err;

    err = nvs_set_blob(handle, key, data, size);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    LOG("Data saved to storage in %s", key);
    return err;
}

esp_err_t storage_load(const char *key, void *data, size_t size) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NS, NVS_READONLY, &handle);

    size_t actual_size = size;
    if (err == ESP_OK) {
        err = nvs_get_blob(handle, key, data, &actual_size);
        nvs_close(handle);
    }

    if (err != ESP_OK || actual_size != size) {
        return ESP_ERR_NVS_NOT_FOUND;
    }
    LOG("Data loaded from %s in storage", key);
    return ESP_OK;
}