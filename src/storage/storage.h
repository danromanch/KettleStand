#pragma once
#define NVS_NS "kettle_cfg"
#define STORAGE_LIMIT "StorageLimit"
#define STORAGE_CALIBR "StorageCalibr"
#define STORAGE_NETWORK "StorageNetwork"
#include "esp_err.h"

esp_err_t storage_init(void);
esp_err_t storage_save(const char *key, const void *data, size_t size);
esp_err_t storage_load(const char *key, void *data, size_t size);