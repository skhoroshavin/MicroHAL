
#include "microhal.h"
#include <core/flash.h>

enum
{
	tick_period_ms   = 1000,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/2000
};

STATIC_ASSERT((sys_clock_period) < 0x10000, test);

void send_msg( const char * pMessage )
{
	while( *pMessage )
	{
		debug_send_byte(*pMessage);
		++pMessage;
	}
}

void send_msg_flash( const char * pMessage )
{
	char c = flash_read_byte(pMessage);
	while( c )
	{
		debug_send_byte( c );
		++pMessage;
		c = flash_read_byte(pMessage);
	}
}

const char g_pMsgOn[]  FLASH = "LED is on!\n\r";
const char g_pMsgOff[] FLASH = "LED is off!\n\r";

int main(void)
{
	uint8_t  led_state   = 0;
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;
	const char * pMsg = g_pMsgOff;

	led_init();
	sys_clock_init();
	debug_init( 9600 );

	for(;;)
	{
		uint8_t cur_tick = sys_clock_value();
		accumulator += (uint8_t)(cur_tick - last_tick);
		last_tick = cur_tick;

		if( accumulator > sys_clock_period )
		{
			accumulator -= sys_clock_period;

			led_state = 1 - led_state;
			pMsg = led_state ? g_pMsgOn : g_pMsgOff;

			led_write( led_state );
			send_msg_flash( pMsg );
		}
	}

	return 0;
}
