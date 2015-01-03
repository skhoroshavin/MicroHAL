
#include <platform/flash.h>
#include <utils/string_utils.h>
#include <system/soft_irq.h>
#include <system/clock.h>
#include <system/console.h>

enum
{
	blink_period = ms2ticks(1000/128)
};

STATIC_ASSERT(blink_period < 0x100, main);

volatile uint16_t led_on  = blink_period/2;
volatile uint16_t led_off = blink_period/2;

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
	{ cmd_led_on,  blink_period-1 },
	{ cmd_led_off, 1 },
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
			led_on = flash_read_word( &cmd_led_args[i].period );
			led_off = blink_period - led_on;
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

void soft_irq_call( uint8_t id )
{
	switch( id )
	{
	case clock_soft_irq_id:
		clock_soft_irq();
		return;
	case console_soft_irq_id:
		console_process();
		return;
	}
}

void soft_irq_idle()
{
	wait_for_irq();
}

tick_t clock_timeout( tick_t dt )
{
	static uint8_t state = 0;

	++state;

	if( state < 128 )
	{
		led_write( 0 );
		return led_off;
	}
	else
	{
		led_write( 1 );
		return led_on;
	}
}

int main(void)
{
	hal_init();

	clock_init();
	console_init( 9600 );

	while(1)
		hal_process();

	return 0;
}
