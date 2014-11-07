
#pragma once

#include <avr/io.h>

typedef uint8_t avr_gpio_t;

#define AVR_DECLARE_GPIO(NAME) \
	inline void avr_gpio##NAME##_write( avr_gpio_t value ) { PORT##NAME = value; } \
	inline avr_gpio_t avr_gpio##NAME##_read() { return PIN##NAME; } \
	\
	inline void avr_gpio##NAME##_set( avr_gpio_t value ) { PORT##NAME |= value; } \
	inline void avr_gpio##NAME##_clr( avr_gpio_t value ) { PORT##NAME &= ~value; } \
	inline void avr_gpio##NAME##_clr_set( avr_gpio_t c, avr_gpio_t s ) { PORT##NAME = (PORT##NAME & ~c) | s; } \
	\
	void avr_gpio##NAME##_init( avr_gpio_t maskOut, avr_gpio_t maskState );

#define AVR_IMPLEMENT_GPIO(NAME) \
	void avr_gpio##NAME##_init( avr_gpio_t maskOut, avr_gpio_t maskState ) \
	{ \
		PORT##NAME = maskState; \
		DDR##NAME  = maskOut; \
	}


#ifdef PORTA
AVR_DECLARE_GPIO(A)
#endif // PORTA

#ifdef PORTB
AVR_DECLARE_GPIO(B)
#endif // PORTB

#ifdef PORTC
AVR_DECLARE_GPIO(C)
#endif // PORTC

#ifdef PORTD
AVR_DECLARE_GPIO(D)
#endif // PORTD

#ifdef PORTE
AVR_DECLARE_GPIO(E)
#endif // PORTE

#ifdef PORTF
AVR_DECLARE_GPIO(F)
#endif // PORTF
