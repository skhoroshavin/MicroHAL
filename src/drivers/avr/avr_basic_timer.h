
#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

enum
{
	_avr_timer_prescaler_bit_1    = 1,
	_avr_timer_prescaler_bit_8    = 2,
	_avr_timer_prescaler_bit_64   = 3,
	_avr_timer_prescaler_bit_256  = 4,
	_avr_timer_prescaler_bit_1024 = 5
};
#define _AVR_BASIC_TIMER_PRESCALER_BIT(value) _avr_timer_prescaler_bit_##value

#define AVR_BASIC_TIMER(name,oca_name,ocb_name,prescaler) \
	typedef uint8_t name##_value_t; \
	enum { name##_freq = cpu_freq/prescaler }; \
	void name##_init(); \
	inline name##_value_t name##_value() { return TCNT0; } \
	inline uint8_t name##_has_overflow() { return TIFR0 & (1 << TOV0); } \
	inline void name##_clear_overflow() { TIFR0 = (1 << TOV0); } \
	inline name##_value_t oca_name##_value() { return OCR0A; } \
	inline void oca_name##_set_value( name##_value_t value ) { OCR0A = value; } \
	inline uint8_t oca_name##_is_set() { return TIFR0 & (1 << OCF0A); } \
	inline void oca_name##_clear() { TIFR0 = (1 << OCF0A); } \
	inline void oca_name##_enable() { TIMSK0 |= (1 << OCIE0A); } \
	inline void oca_name##_disable() { TIMSK0 &= (uint8_t)(~(1 << OCIE0A)); } \
	inline name##_value_t ocb_name##_value() { return OCR0B; } \
	inline void ocb_name##_set_value( name##_value_t value ) { OCR0B = value; } \
	inline uint8_t ocb_name##_is_set() { return TIFR0 & (1 << OCF0B); } \
	inline void ocb_name##_clear() { TIFR0 = (1 << OCF0B); }

#define IMPLEMENT_AVR_BASIC_TIMER(name,prescaler) \
	void name##_init() \
	{ \
		TCCR0A = 0; \
		TCCR0B = _AVR_BASIC_TIMER_PRESCALER_BIT(prescaler); \
	} \
	ISR(TIMER0_COMPA_vect) { }
