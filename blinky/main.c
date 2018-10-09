#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

/**
 * Main entry
 */
void sdk_init_done_cb(void);

os_timer_t start_timer;

void start_timer_cb(void *arg) {
	static int on = 0;
	if (!on) { /* if LED is OFF - turn it on */
		gpio_output_set(BIT16, 0, BIT16, 0);
		on = 1;
	} else { /* if LED is ON - turn is off */
		gpio_output_set(0, BIT12, BIT12, 0);
		on = 0;
	}
}

void user_init()
{
    // set up UART0 to 9600 baud 8N1
    uart_div_modify(0, UART_CLK_FREQ / 9600);
    system_init_done_cb(sdk_init_done_cb);

    os_printf("\nESP8266 says hello\n\n");
}

void sdk_init_done_cb(void) {
	os_timer_disarm(&start_timer);
	os_timer_setfn(&start_timer, start_timer_cb, NULL); /* Set callback for timer */
	os_timer_arm(&start_timer, 5000 /* call every 5 second */, 1 /* repeat */);
}
