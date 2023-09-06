#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

void toggle_LED(const struct device *dev, gpio_pin_t pin_num, bool *led_status, int *counter);

int led_setup(const struct device *dev, bool* led_status, gpio_pin_t led_pin, gpio_flags_t led_flags, int *counter);
