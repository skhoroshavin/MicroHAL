
#include <hal.h>

#define CPU_FREQ    16000000
#define TIMER_FREQ  (CPU_FREQ/1024)
#define CNT_FREQ    (TIMER_FREQ/256)

int main(void)
{
	uint8_t counter   = 0;
	uint8_t led_state = 0;

	halInit();

	while(1)
	{
		halProcess();

		if( avr_basic_timer_overflow() )
		{
			avr_basic_timer_clear_overflow();
			++counter;
		}

		if( counter > CNT_FREQ )
		{
			led_state = 1 - led_state;
			counter = 0;
		}

		LED_write( led_state );
	}

	return 0;
}
