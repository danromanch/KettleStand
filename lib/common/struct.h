#pragma once

#include <stdint.h>

typedef struct {
   float maxTemp;
   uint8_t minWater;
} block_limit_t;

typedef struct {
    uint8_t loadCellScale;
} block_calib_t;

typedef struct {
    char ssid[32];
    char password[32];
} block_network_t;

typedef struct {
    float temperature;
    uint8_t waterLevel;
} state_sensor_t;