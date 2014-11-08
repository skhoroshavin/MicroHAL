
#include <hal.h>

#define CPU_FREQ    16000000
#define TIMER_FREQ  (CPU_FREQ/1024)

int main(void)
{
	uint8_t led_state = 0;

	halInit();
	avr_advanced_timer_set_top(TIMER_FREQ);

	for(;;)
	{
		halProcess();

		if( timer_has_top(MAIN_TIMER) )
		{
			timer_clear_top(MAIN_TIMER);
			led_state = 1 - led_state;
		}

		gpio_write_pin(LED,led_state);
	}

	return 0;
}
