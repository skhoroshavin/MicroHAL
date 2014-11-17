
#include "microhal.h"

enum
{
	tick_period_ms   = 500,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT((sys_clock_period) < 0x10000, test);

int main(void)
{
	uint8_t  led_state   = 0;
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;

	halInit();

	for(;;)
	{
		uint8_t cur_tick = sys_clock_value();
		accumulator += (uint8_t)(cur_tick - last_tick);
		last_tick = cur_tick;

		if( accumulator > sys_clock_period )
		{
			accumulator -= sys_clock_period;

			led_state = 1 - led_state;
			char c = led_state ? '1' : '0';

			led_write(led_state);
			avr_uart_send_blocking(c);
		}
	}

	return 0;
}
