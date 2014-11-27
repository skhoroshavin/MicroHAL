
#include "microhal.h"
#include <core/flash.h>
#include <core/int_to_string.h>
#include <core/buffer.h>
#include <core/string_utils.h>
#include <core/text_output.h>
#include <core/text_input.h>

enum
{
	tick_period_ms   = 1000,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT(sys_clock_period < 0x10000, main);

volatile uint16_t led_on = sys_clock_freq/2;

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

void process_input( uint8_t argc, const char * argv[] )
{
	static const char unknown_cmd[] FLASH = "Unknown command: ";
	static const char endl[] FLASH = "\n\r";

	static const char usage_led[] FLASH =
			"Usage: led <parameter>\r\n"
			"Valid parameters are: on, off, blink, flash\r\n";

	static const char cmd_led[]       FLASH = "led";
	static const char cmd_led_on[]    FLASH = "on";
	static const char cmd_led_off[]   FLASH = "off";
	static const char cmd_led_blink[] FLASH = "blink";
	static const char cmd_led_flash[] FLASH = "flash";

	if( str_equalF( argv[0], cmd_led ) )
	{
		if( argc < 2 )
		{
			output_send_flash_str( &out, usage_led );
			return;
		}

		if( str_equalF( argv[1], cmd_led_on ) )
			led_on = sys_clock_period;
		else if( str_equalF( argv[1], cmd_led_off ) )
			led_on = 0;
		else if( str_equalF( argv[1], cmd_led_blink ) )
			led_on = sys_clock_period / 2;
		else if( str_equalF( argv[1], cmd_led_flash ) )
			led_on = sys_clock_period / 20;
		else
			output_send_flash_str( &out, usage_led );
	}
	else
	{
		output_send_flash_str( &out, unknown_cmd );
		output_send_mem_str( &out, argv[0] );
		output_send_flash_str( &out, endl );
	}
}

int main(void)
{
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;

	led_init();
	sys_clock_init();

	debug_init( 9600 );
	input_init( &in );
	output_init( &out );

	for(;;)
	{
		uint8_t cur_tick = sys_clock_value();
		accumulator += (uint8_t)(cur_tick - last_tick);
		if( accumulator > sys_clock_period )
			accumulator -= sys_clock_period;
		last_tick = cur_tick;

		led_write( accumulator < led_on );

		input_process( &in );
		output_process( &out );
	}

	return 0;
}
