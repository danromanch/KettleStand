#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "pins.h"

void configPins(void)
{
    gpio_config_t rly_conf = {
        .pin_bit_mask = (1ULL << RLY_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&rly_conf);
}
