
#pragma once

/***********************************************************************\
 * System configuration                                                *
\***********************************************************************/

enum
{
	cpu_freq = 16000000
};

/***********************************************************************\
 * Soft IRQ configuration                                              *
\***********************************************************************/

enum
{
	clock_soft_irq_id,
	console_soft_irq_id,

	soft_irq_count
};

/***********************************************************************\
 * Clock configuration                                                 *
\***********************************************************************/

#include <drivers/avr/avr_timer.h>
AVR_BASIC_TIMER(clock_timer,1024)
AVR_TIMER_COMPARE(clock_compare,clock_timer_t,0,A)

#include <drivers/soft/soft_timer.h>
SOFT_TIMER(test_timer, clock_timer, uint16_t, 1, 65536)

#include <drivers/soft/soft_timer_compare.h>
SOFT_TIMER_COMPARE(test_compare, test_timer)

/***********************************************************************\
 * GPIO                                                                *
\***********************************************************************/

#include <drivers/avr/avr_gpio.h>
AVR_GPIO_OUTPUT(led, B,5,1, 0)
AVR_GPIO_OUTPUT(dbg, B,4,1, 0)

/***********************************************************************\
 * Timers                                                              *
\***********************************************************************/

/***********************************************************************\
 * UART                                                                *
\***********************************************************************/

#include <drivers/avr/avr_uart.h>
AVR_UART(console_uart,0)
