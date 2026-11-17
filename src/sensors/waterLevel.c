#include <stdint.h>
static uint8_t waterLevel = 0;

void updateWaterLevel(void)
{
    // TODO implement update
    waterLevel = 11;
}

uint8_t getWaterLevel(void)
{
    return waterLevel;
}