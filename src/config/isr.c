#include "driver/gpio.h"
#include "lib/common/pins.h"
#include "ui/button.h"

void configISR(void)
{
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BTN_PIN, buttonPress, NULL);
}