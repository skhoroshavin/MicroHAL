
#include <hal.h>

void halInit()
{
	gpio_setup_pin( LED, AVR_GPIO_OUTPUT_LOW );

	avr_basic_timer_init( AVR_BASIC_TIMER_CLK_1024 );
}

void halProcess()
{

}
