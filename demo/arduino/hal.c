
#include "hal.h"

IMPLEMENT_AVR_TIMER_COMPARE(clock_compare,0,A)

IMPLEMENT_SOFT_TIMER(test_timer,clock_timer)
