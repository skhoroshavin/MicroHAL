
#pragma once

#include <platform/interrupts.h>
#include <utils/bit_utils.h>
#include <utils/pp_utils.h>

enum
{
	_avr_timer_prescaler_bit_1    = 1,
	_avr_timer_prescaler_bit_8    = 2,
	_avr_timer_prescaler_bit_64   = 3,
	_avr_timer_prescaler_bit_256  = 4,
	_avr_timer_prescaler_bit_1024 = 5
};

#define AVR_TIMER_8(name,prescaler,timer) \
	typedef uint8_t name##_value_t; \
	enum { \
		name##_prescaler = prescaler, \
		name##_prescaler_bit = _avr_timer_prescaler_bit_##prescaler, \
		name##_freq = cpu_freq/prescaler \
	}; \
	inline uint8_t name##_value() { return TCNT##timer; } \
	inline void name##_set_value( uint8_t value ) { TCNT##timer = value; } \
	inline void name##_start() { MASKED_WRITE( TCCR##timer##B, 0, 3, name##_prescaler_bit ); } \
	inline void name##_stop()  { MASKED_WRITE( TCCR##timer##B, 0, 3, 0 ); }

#define AVR_TIMER_COMP_8(name,timer,comp) \
	inline uint8_t name##_value() { return OCR##timer##comp; } \
	inline void name##_set_value( uint8_t value ) { OCR##timer##comp = value; } \
	inline void name##_irq_enable() { TIMSK##timer |= (1 << OCIE##timer##comp); } \
	inline void name##_irq_disable() { TIMSK##timer &= (uint8_t)(~(1 << OCIE##timer##comp)); } \
	void name##_irq();

#define AVR_IMPLEMENT_TIMER_COMP(name,timer,comp) \
	ISR(TIMER##timer##_COMP##comp##_vect) { name##_irq(); } \
	void __attribute__ ((weak)) name##_irq() { }
