#include <stdint.h>

static float temperature = 0;

void updateTemperature(void)
{
   //TODO implement update
   temperature = 99;
   return; 
}

uint8_t getTemperature(void)
{
    return temperature; 
}

