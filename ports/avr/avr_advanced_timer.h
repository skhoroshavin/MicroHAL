
#pragma once

#include <ports/avr/_avr_timer_utils.h>

#define AVR_ADVANCED_TIMER_NORMAL(name,index,prescaler) \
	enum { name##_freq = cpu_freq/prescaler }; \
	inline void name##_init() \
	{ \
		TCCR0A = 0; \
		TCCR0B = _AVR_TIMER_PRESCALER_BIT(prescaler); \
	} \
	inline uint16_t name##_value() { return TCNT; }







#define avr_advanced_timer_counter()          (TCNT1)
#define avr_advanced_timer_set_counter(VALUE) do { TCNT1 = (VALUE); } while(0)
#define avr_advanced_timer_set_top(VALUE)     do { OCR1A = (VALUE); } while(0)

#define avr_advanced_timer_has_overflow()   (TIFR1 & (1 << TOV1))
#define avr_advanced_timer_clear_overflow() do { TIFR1 |= (1 << TOV1); } while(0)

#define avr_advanced_timer_has_top()   (TIFR1 & (1 << OCF1A))
#define avr_advanced_timer_clear_top() do { TIFR1 |= (1 << OCF1A); } while(0)

typedef enum
{
	AVR_ADVANCED_TIMER_MODE_NORMAL        = 0,
	AVR_ADVANCED_TIMER_MODE_PWM_SYMMETRIC = 1,
	AVR_ADVANCED_TIMER_MODE_CTC           = 4,
	AVR_ADVANCED_TIMER_MODE_PWM           = 5
} avr_advanced_timer_mode_t;

typedef struct
{
	avr_timer_clock_t         clock;
	avr_advanced_timer_mode_t mode;
	avr_timer_pwm_t           pwm_a;
	avr_timer_pwm_t           pwm_b;
} avr_advanced_timer_config_t;

void avr_advanced_timer_setup( const avr_advanced_timer_config_t * config );
