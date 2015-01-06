
#pragma once

#include <drivers/common/timer.h>

#include <platform/interrupts.h>
#include <utils/bit_utils.h>
#include <utils/pp_utils.h>

#ifndef TIMER0_COMPA_vect
#define TIMER0_COMPA_vect TIM0_COMPA_vect
#endif /* TIMER0_COMPA_vect */

enum
{
	_avr_timer_prescaler_bit_1    = 1,
	_avr_timer_prescaler_bit_8    = 2,
	_avr_timer_prescaler_bit_64   = 3,
	_avr_timer_prescaler_bit_256  = 4,
	_avr_timer_prescaler_bit_1024 = 5
};

#define AVR_TIMER_COMMON(name, timer, prescaler) \
	enum { name##_prescaler_bit = _avr_timer_prescaler_bit_##prescaler }; \
	inline void name##_start() { MASKED_WRITE( TCCR##timer##B, 0, 3, name##_prescaler_bit ); } \
	inline void name##_stop()  { MASKED_WRITE( TCCR##timer##B, 0, 3, 0 ); }

#define AVR_BASIC_TIMER(name, prescaler) \
	TIMER_COMMON(name, uint8_t, cpu_freq/(prescaler), 256, TCNT0, none, none) \
	AVR_TIMER_COMMON(name, 0, prescaler)

#define AVR_ADVANCED_TIMER(name, timer, prescaler) \
	TIMER_COMMON(name, uint16_t, cpu_freq/(prescaler), 65536, TCNT##timer, none, none) \
	AVR_TIMER_COMMON(name, timer, prescaler)

#define AVR_TIMER_COMPARE(name, type, timer, comp) \
	PROPERTY_REG_RW(name, type, OCR##timer##comp, none, none) \
	inline void name##_irq_enable() { TIMSK##timer |= (1 << OCIE##timer##comp); } \
	inline void name##_irq_disable() { TIMSK##timer &= (uint8_t)(~(1 << OCIE##timer##comp)); } \
	void name##_irq();

#define IMPLEMENT_AVR_TIMER_COMPARE(name,timer,comp) \
	ISR(TIMER##timer##_COMP##comp##_vect) { name##_irq(); }
