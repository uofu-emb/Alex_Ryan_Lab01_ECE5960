#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "blink.h"

void toggle_LED(const struct device *dev, gpio_pin_t pin_num, bool *led_status, int *counter)
{
    counter = counter + 1;
	gpio_pin_set(dev, pin_num, (int) *led_status);
	*led_status = !*led_status;
}

int led_setup(const struct device *dev, bool* led_status, gpio_pin_t led_pin, gpio_flags_t led_flags, int *counter)
{
    *counter = 0;
    int ret = gpio_pin_configure(dev, led_pin, led_flags);
    *led_status = true;
    return ret;
}