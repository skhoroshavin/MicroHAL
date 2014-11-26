
#include "microhal.h"
#include <core/flash.h>
#include <core/int_to_string.h>
#include <core/buffer.h>
#include <core/text_output.h>
#include <core/text_input.h>

enum
{
	tick_period_ms   = 4000,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT(sys_clock_period < 0x10000, main);

buffered_output_t out =
{
	.send     = debug_send,
	.can_send = debug_can_send
};

const char g_pMsgOn[]   FLASH = "LED is on!\n\r";
const char g_pMsgOff[]  FLASH = "LED is off!\n\r";
const char g_pMsgSize[] FLASH = "Size: ";
const char g_pMsgRecv[] FLASH = "Message: ";
const char g_pMgsEndl[] FLASH = "\n\r";

struct
{
	uint8_t size;
	char    data[16];
} buffer;

void process_uart()
{
	while( debug_can_recv() )
	{
		char c = debug_recv();
		buf_push_back( &buffer, c );
	}
}

int main(void)
{
	uint8_t  led_state   = 0;
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;
	const char * pMsg = g_pMsgOff;
	char     buf[32];

	led_init();
	sys_clock_init();
	debug_init( 9600 );
	output_init( &out );
	buf_init( &buffer );

	for(;;)
	{
		process_uart();
		output_process( &out );

		uint8_t cur_tick = sys_clock_value();
		accumulator += (uint8_t)(cur_tick - last_tick);
		last_tick = cur_tick;

		if( accumulator > sys_clock_period )
		{
			accumulator -= sys_clock_period;

			led_state = 1 - led_state;
			pMsg = led_state ? g_pMsgOn : g_pMsgOff;

			led_write( led_state );
			output_send_flash_str( &out, pMsg );

			output_send_flash_str( &out, g_pMsgSize );
			*write_uint16( buf, buf_size( &buffer ) ) = 0;
			output_send_mem_str( &out, buf );
			output_send_flash_str( &out, g_pMgsEndl );

			output_send_flash_str( &out, g_pMsgRecv );
			buf_push_back( &buffer, 0 );
			output_send_mem_str( &out, buffer.data );
			buf_clear( &buffer );
			output_send_flash_str( &out, g_pMgsEndl );
		}
	}

	return 0;
}
