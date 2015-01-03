
#include "hal.h"
#include <system/soft_irq.h>

IMPLEMENT_SOFT_TIMER(clock_timer,clock_timer_base)
IMPLEMENT_SOFT_TIMER_COMPARE(clock_compare,clock_timer)

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
	clock_compare_process();

	soft_irq_process();
}
