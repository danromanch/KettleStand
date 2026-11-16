#include <stdint.h>

static float waterLevel = 0;

void updateWaterLevel(void)
{
    // TODO implement update
    waterLevel = 11;
}

uint8_t getWaterLevel(void)
{
    return waterLevel;
}