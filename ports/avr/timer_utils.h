
#pragma once

#include <core/timer.h>

typedef enum
{
	AVR_TIMER_OFF      = 0,
	AVR_TIMER_CLK      = 1,
	AVR_TIMER_CLK_8    = 2,
	AVR_TIMER_CLK_64   = 3,
	AVR_TIMER_CLK_256  = 4,
	AVR_TIMER_CLK_1024 = 5
} avr_timer_clock_t;

typedef enum
{
	AVR_TIMER_MODE_NORMAL        = 0,
	AVR_TIMER_MODE_PWM_SYMMETRIC = 1,
	AVR_TIMER_MODE_CTC           = 2,
	AVR_TIMER_MODE_PWM           = 3
} avr_timer_mode_t;

typedef enum
{
	AVR_TIMER_PWM_OFF      = 0,
	AVR_TIMER_PWM_CTC_FM   = 1,
	AVR_TIMER_PWM_NORMAL   = 2,
	AVR_TIMER_PWM_INVERTED = 3
} avr_timer_pwm_t;
