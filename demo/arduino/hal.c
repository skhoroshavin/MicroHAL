
#include "hal.h"
#include <system/soft_irq.h>

IMPLEMENT_AVR_TIMER_COMPARE(clock_compare,0,A)

IMPLEMENT_SOFT_TIMER(test_timer,clock_timer)
IMPLEMENT_SOFT_TIMER_COMPARE(test_compare,test_timer)

void test_compare_irq()
{

}

void hal_init()
{
	led_init();
	dbg_init();
}

void hal_process()
{
	irq_enable();
//	test_timer_process();
//	test_compare_process();

	soft_irq_process();
}
