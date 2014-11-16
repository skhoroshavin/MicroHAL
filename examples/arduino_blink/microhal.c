
#include "microhal.h"

void halInit()
{
	led_init();

	avr_advanced_timer_config_t timer_config =
	{
		.clock  = AVR_TIMER_CLK_1024,
		.mode   = AVR_ADVANCED_TIMER_MODE_CTC,
		.pwm_a  = AVR_TIMER_PWM_OFF,
		.pwm_b  = AVR_TIMER_PWM_OFF
	};
	avr_advanced_timer_setup( &timer_config );

	avr_uart_init( 9600 );
}

void halProcess()
{

}
