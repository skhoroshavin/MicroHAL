
#include "hal.h"
#include <system/soft_irq.h>

IMPLEMENT_AVR_TIMER_COMPARE(clock_timer_base_compare,0,A)

IMPLEMENT_SOFT_TIMER(clock_timer,clock_timer_base)
IMPLEMENT_SOFT_TIMER_COMPARE_IRQ(clock_compare,clock_timer,clock_timer_base,clock_timer_base_compare)

void clock_timer_base_compare_irq()
{
	clock_compare_process();
}

void hal_init()
{
	led_init();
	dbg_init();

	clock_timer_init();
	clock_compare_init();

	clock_timer_base_start();
}

void hal_process()
{
	irq_enable();
	clock_timer_process();

	soft_irq_process();
}
