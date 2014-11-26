
#include "microhal.h"
#include <core/flash.h>
#include <core/int_to_string.h>
#include <core/buffer.h>
#include <core/text_output.h>
#include <core/text_input.h>

enum
{
	tick_period_ms   = 500,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT(sys_clock_period < 0x10000, main);

void process_input( uint8_t argc, const char * argv[] );

buffered_input_t in =
{
	.recv     = debug_recv,
	.can_recv = debug_can_recv,
	.process  = process_input
};

buffered_output_t out =
{
	.send     = debug_send,
	.can_send = debug_can_send
};

const char g_pMsgOn[]   FLASH = "LED is on!\n\r";
const char g_pMsgOff[]  FLASH = "LED is off!\n\r";
const char g_pMsgSize[] FLASH = "Arguments: ";
const char g_pMgsEndl[] FLASH = "\n\r";

void process_input( uint8_t argc, const char * argv[] )
{
	char buf[32];
	uint8_t i;

	output_send_flash_str( &out, g_pMsgSize );
	*write_uint16( buf, argc ) = 0;
	output_send_mem_str( &out, buf );
	output_send_flash_str( &out, g_pMgsEndl );

	for( i = 0; i < argc; ++i )
	{
		output_send_mem_str( &out, argv[i] );
		output_send_flash_str( &out, g_pMgsEndl );
	}
}

int main(void)
{
	uint8_t  led_state   = 0;
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;
	const char * pMsg = g_pMsgOff;

	led_init();
	sys_clock_init();

	debug_init( 9600 );
	input_init( &in );
	output_init( &out );

	for(;;)
	{
		input_process( &in );
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
		}
	}

	return 0;
}
