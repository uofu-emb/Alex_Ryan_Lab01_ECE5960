#include <unity.h>
#include <stdint.h>
#include <stdio.h>
#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <blink.h>

#define LED_NODE DT_ALIAS(led3)
#define LED DT_GPIO_LABEL(LED_NODE, gpios)
#define PIN DT_GPIO_PIN(LED_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED_NODE, gpios)

void setUp () {}

void tearDown(){}

void test_led_enable(void) 
{
    int counter;
    bool led_is_on;
    const struct device *dev = device_get_binding(LED);
    int ret = led_setup(dev, &led_is_on, PIN, GPIO_OUTPUT_ACTIVE | FLAGS, &counter);
    TEST_ASSERT_EQUAL_MESSAGE(0, ret, "LED was not set up properly.");
    TEST_ASSERT_TRUE_MESSAGE(led_is_on, "LED should start toggled off");
    toggle_LED(dev, PIN, &led_is_on, &counter);
    TEST_ASSERT_TRUE_MESSAGE(!led_is_on, "LED should have changed to on.");
    TEST_ASSERT_TRUE_MESSAGE(gpio_pin_get(dev, PIN), "GPIO should report on");
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_led_enable);
    return UNITY_END();
}