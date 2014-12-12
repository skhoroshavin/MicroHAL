
#include "microhal.h"
#include <core/flash.h>
#include <core/int_to_string.h>
#include <core/buffer.h>
#include <core/string_utils.h>
#include <core/console.h>
#include <core/task.h>
#include <core/task_table.h>

enum
{
	tick_period_ms = 1000,
	blink_period   = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT(blink_period < 0x10000, main);

BEGIN_CONTEXT(blink_t)
	uint16_t led_on;
	uint16_t led_off;
END_CONTEXT(blink_t)

blink_t blink_context =
{
	.led_on  = blink_period/2,
	.led_off = blink_period/2
};

FLASH_STR(unknown_cmd) = "Unknown command: ";
FLASH_STR(endl)        = "\n\r";

FLASH_STR(usage_led)   =
		"Usage: led <parameter>\r\n"
		"Valid parameters are: on, off, blink, flash\r\n";
FLASH_STR(cmd_led) = "led";
FLASH_STR(cmd_led_on) = "on";
FLASH_STR(cmd_led_off) = "off";
FLASH_STR(cmd_led_blink) = "blink";
FLASH_STR(cmd_led_flash) = "flash";

struct cmd_led_arg_t
{
	flash_str name;
	uint16_t  period;
};

FLASH_DATA(struct cmd_led_arg_t,cmd_led_args) =
{
	{ cmd_led_on, blink_period },
	{ cmd_led_off, 0 },
	{ cmd_led_blink, blink_period/2 },
	{ cmd_led_flash, blink_period/20 },
	{ 0, 0 }
};

void console_on_command( uint8_t argc, const char * argv[] )
{
	if( str_equalF( argv[0], cmd_led ) )
	{
		if( argc < 2 )
		{
			console_print( usage_led );
			return;
		}

		uint8_t i = str_findF( argv[1], cmd_led_args, sizeof(struct cmd_led_arg_t) );
		if( i < array_size(cmd_led_args) )
		{
			blink_context.led_on = flash_read_word( &cmd_led_args[i].period );
			blink_context.led_off = blink_period - blink_context.led_on;
		}
		else
		{
			console_print( usage_led );
		}
	}
	else
	{
		console_print( unknown_cmd );
		output_send_mem_str( &_console_output, argv[0] );
		console_print( endl );
	}
}

unsigned blink_handler( blink_t * ctx )
{
	task_begin(ctx);

	while(1)
	{
		if( ctx->led_on )
		{
			led_write( 1 );
			task_delay( ctx, ctx->led_on );
		}

		if( ctx->led_off )
		{
			led_write( 0 );
			task_delay( ctx, ctx->led_off );
		}
	}

	task_end(ctx);
}

BEGIN_TASK_TABLE(tasks)
	TASK_ENTRY(&blink_handler,&blink_context)
END_TASK_TABLE()

int main(void)
{
	uint8_t last_tick = sys_clock_value();

	led_init();
	sys_clock_init();
	console_init( 9600 );

	for(;;)
	{
		uint8_t dt = sys_clock_value() - last_tick;
		task_table_process( tasks, dt );
		last_tick += dt;

		console_process();
	}

	return 0;
}
