
#include "hal.h"
#include <system/soft_irq.h>

IMPLEMENT_AVR_TIMER_COMPARE(clock_compare, 1, A)

void hal_init()
{
	CLKPR = 0x80;
	CLKPR = 0x00;

	led_init();
	dbg_init();

	clock_timer_start();
}

void hal_process()
{
	irq_enable();
	soft_irq_process();
}
