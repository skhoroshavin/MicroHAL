
#include <hal.h>
#include <core/gpio.h>
#include <core/timer.h>

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

		if( TIMER_HAS_OVERFLOW(MAIN_TIMER) )
		{
			TIMER_CLEAR_OVERFLOW(MAIN_TIMER);
			++counter;
		}

		if( counter > CNT_FREQ )
		{
			led_state = 1 - led_state;
			counter = 0;
		}

		GPIO_PIN_WRITE(LED,led_state);
	}

	return 0;
}
