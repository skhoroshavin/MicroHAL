
#include "microhal.h"

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
			char c = led_state ? '1' : '0';

			led_write(led_state);
			avr_uart_send_blocking(c);
		}
	}

	return 0;
}
