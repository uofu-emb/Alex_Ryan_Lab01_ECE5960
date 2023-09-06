#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "blink.h"

void toggle_LED(const struct device *dev, gpio_pin_t pin_num, bool *led_status)
{
	gpio_pin_set(dev, pin_num, (int) *led_status);
	*led_status = !*led_status;
}

const struct device * led_setup(const char *led_name, bool* led_status, gpio_pin_t led_pin, gpio_flags_t led_flags)
{
    const struct device *dev = device_get_binding(led_name);
    int ret = gpio_pin_configure(dev, led_pin, led_flags);
    *led_status = true;
    return dev;
}