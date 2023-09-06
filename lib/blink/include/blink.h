#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>

void toggle_LED(const struct device *dev, gpio_pin_t pin_num, bool *led_status);

const struct device * led_setup(const char *led_name, bool* led_status, gpio_pin_t led_pin, gpio_flags_t led_flags);
