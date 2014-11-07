
#include <hal.h>

#define CPU_FREQ    16000000
#define TIMER_FREQ  (CPU_FREQ/1024)
#define CNT_FREQ    (TIMER_FREQ/256)

int main(void)
{
	uint8_t counter   = 0;
	uint8_t led_state = 0;

	halInit();

	for(;;)
	{
		halProcess();

		if( timer_has_overflow(MAIN_TIMER) )
		{
			timer_clear_overflow(MAIN_TIMER);
			++counter;
		}

		if( counter > CNT_FREQ )
		{
			led_state = 1 - led_state;
			counter = 0;
		}

		gpio_write_pin(LED,led_state);
	}

	return 0;
}
