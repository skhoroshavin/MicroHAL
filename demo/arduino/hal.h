
#pragma once

/***********************************************************************\
 * Configuration                                                       *
\***********************************************************************/

enum
{
	cpu_freq      = 16000000,

	sched_period  = 256,
	sched_latency = 2
};

/***********************************************************************\
 * GPIO                                                                *
\***********************************************************************/

#include <drivers/avr/avr_gpio.h>
AVR_GPIO_OUTPUT(led, B,5,1, 0)
AVR_GPIO_OUTPUT(dbg, B,4,1, 0)

/***********************************************************************\
 * Timers                                                              *
\***********************************************************************/

#include <drivers/avr/avr_timer.h>
AVR_TIMER_8(sched_timer,1024,0)
AVR_TIMER_COMP_8(sched_compare,0,A)

/***********************************************************************\
 * UART                                                                *
\***********************************************************************/

#include <drivers/avr/avr_uart.h>
AVR_UART(console_uart,0)
