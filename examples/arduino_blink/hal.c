
#include <hal.h>

void halInit()
{
	avr_gpioB_init( 0xff, 0x00 );
	avr_basic_timer_init( AVR_BASIC_TIMER_CLK_1024 );
}

void halProcess()
{

}
