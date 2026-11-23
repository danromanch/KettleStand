#include "esp_attr.h"
#include "button.h"

volatile bool buttonState = false;

void IRAM_ATTR buttonPress(void *arg) 
{
    buttonState = !buttonState;
}