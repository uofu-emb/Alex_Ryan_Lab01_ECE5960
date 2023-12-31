#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include "blink.h"

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
#define LED0	DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN0	DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS0	DT_GPIO_FLAGS(LED0_NODE, gpios)
#define LED1	DT_GPIO_LABEL(LED1_NODE, gpios)
#define PIN1	DT_GPIO_PIN(LED1_NODE, gpios)
#define FLAGS1	DT_GPIO_FLAGS(LED1_NODE, gpios)
#else
/* A build error here means your board isn't set up to blink an LED. */
#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0	""
#define PIN0	0
#define FLAGS0	0
#define LED1	""
#define PIN1	0
#define FLAGS1	0
#endif

#define STACKSIZE 2000

struct k_thread coop_thread;
K_THREAD_STACK_DEFINE(coop_stack, STACKSIZE);
int counter;
bool led_is_on;


void thread_entry(void)
{
    // Get the same values for LED1 as at the beginning of main for LED0
	bool led_is_on;
    const struct device *dev = device_get_binding(LED1);
	int ret = led_setup(dev, &led_is_on, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS0, &counter);
    
    // Set up a k_timer to keep track of time
	struct k_timer t;
	k_timer_init(&t, NULL, NULL);

    // Increment a counter every time the loop runs and change the status of the LED.
	while (1) {
		toggle_LED(dev, PIN1, &led_is_on, &counter);
        // Start the k_timer on an interval of 2 seconds. 
		k_timer_start(&t, K_MSEC(2000), K_NO_WAIT);
		k_timer_status_sync(&t);
	}
}

void main(void)
{
	int counter;
    // Create a device struct pointer, assume led is on, and create a local int to capture return value of configure.
	const struct device *dev = device_get_binding(LED0);
	int ret = led_setup(dev, &led_is_on, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0, &counter);

    // Create a thread for doing stuff related to a k_thread.
    k_thread_create(&coop_thread,
                    coop_stack,
                    STACKSIZE,
                    (k_thread_entry_t) thread_entry,
                    NULL,
                    NULL,
                    NULL,
                    K_PRIO_COOP(7),
                    0,
                    K_NO_WAIT);

    // If the LED device wasn't configured correctly, exit early
	if (dev == NULL) {
		return;
	}
	if (ret != 0) {
		return;
	}
    // Alternate the status of the LED every half second.
	while (1) {
		toggle_LED(dev, PIN0, &led_is_on, &counter);
		k_msleep(500);
	}
}