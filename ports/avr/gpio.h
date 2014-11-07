
#pragma once

#include <avr/io.h>
#include <core/gpio.h>

typedef enum
{
	_AVR_HIGH   = (1 << 0),
	_AVR_OUTPUT = (1 << 1),

	AVR_GPIO_INPUT_HIZ      = 0,
	AVR_GPIO_INPUT_PULLUP   = _AVR_HIGH,

	AVR_GPIO_OUTPUT_LOW     = _AVR_OUTPUT,
	AVR_GPIO_OUTPUT_HIGH    = _AVR_OUTPUT | _AVR_HIGH,

	AVR_GPIO_OPENDRAIN_ACQUIRE = _AVR_OUTPUT,
	AVR_GPIO_OPENDRAIN_RELEASE = 0
} avr_gpio_mode_t;

void avr_gpio_setup( volatile uint8_t * portReg, volatile uint8_t * ddrReg,
					 avr_gpio_mode_t mode, uint8_t start, uint8_t count );

/***********************************************************************\
 * Port B                                                              *
\***********************************************************************/

#ifdef PORTB

#define avr_gpio_b_read()       (PINB)
#define avr_gpio_b_write(VALUE) do { PORTB = VALUE; } while(0)
#define avr_gpio_b_set(VALUE)   do { PORTB |= (VALUE); } while(0)
#define avr_gpio_b_clear(VALUE) do { PORTB &= ~(VALUE); } while(0)
#define avr_gpio_b_masked_set(MASK,VALUE) \
	do { PORTB = (PORTB & ~(MASK)) | (VALUE); }

#define avr_gpio_b_opendrain_read()       (PINB)
#define avr_gpio_b_opendrain_write(VALUE) do { DDRB = VALUE; } while(0)
#define avr_gpio_b_opendrain_set(VALUE)   do { DDRB |= (VALUE); } while(0)
#define avr_gpio_b_opendrain_clear(VALUE) do { DDRB &= ~(VALUE); } while(0)
#define avr_gpio_b_opendrain_masked_set(MASK,VALUE) \
	do { DDRB = (DDRB & ~(MASK)) | (VALUE); }

#define avr_gpio_b_setup(MODE,START,COUNT) avr_gpio_setup(&PORTB,&DDRB,MODE,START,COUNT)

#endif // PORTB

/***********************************************************************\
 * Port C                                                              *
\***********************************************************************/

#ifdef PORTC

#define avr_gpio_c_read()       (PINC)
#define avr_gpio_c_write(VALUE) do { PORTC = VALUE; } while(0)
#define avr_gpio_c_set(VALUE)   do { PORTC |= (VALUE); } while(0)
#define avr_gpio_c_clear(VALUE) do { PORTC &= ~(VALUE); } while(0)
#define avr_gpio_c_masked_set(MASK,VALUE) \
	do { PORTC = (PORTC & ~(MASK)) | (VALUE); }

#define avr_gpio_c_opendrain_read()       (PINC)
#define avr_gpio_c_opendrain_write(VALUE) do { DDRC = VALUE; } while(0)
#define avr_gpio_c_opendrain_set(VALUE)   do { DDRC |= (VALUE); } while(0)
#define avr_gpio_c_opendrain_clear(VALUE) do { DDRC &= ~(VALUE); } while(0)
#define avr_gpio_c_opendrain_masked_set(MASK,VALUE) \
	do { DDRC = (DDRC & ~(MASK)) | (VALUE); }

#define avr_gpio_c_setup(MODE,START,COUNT) avr_gpio_setup(&PORTC,&DDRC,MODE,START,COUNT)

#endif // PORTC

/***********************************************************************\
 * Port D                                                              *
\***********************************************************************/

#ifdef PORTD

#define avr_gpio_d_read()       (PIND)
#define avr_gpio_d_write(VALUE) do { PORTD = VALUE; } while(0)
#define avr_gpio_d_set(VALUE)   do { PORTD |= (VALUE); } while(0)
#define avr_gpio_d_clear(VALUE) do { PORTD &= ~(VALUE); } while(0)
#define avr_gpio_d_masked_set(MASK,VALUE) \
	do { PORTD = (PORTD & ~(MASK)) | (VALUE); }

#define avr_gpio_d_opendrain_read()       (PIND)
#define avr_gpio_d_opendrain_write(VALUE) do { DDRD = VALUE; } while(0)
#define avr_gpio_d_opendrain_set(VALUE)   do { DDRD |= (VALUE); } while(0)
#define avr_gpio_d_opendrain_clear(VALUE) do { DDRD &= ~(VALUE); } while(0)
#define avr_gpio_d_opendrain_masked_set(MASK,VALUE) \
	do { DDRD = (DDRD & ~(MASK)) | (VALUE); }

#define avr_gpio_d_setup(MODE,START,COUNT) avr_gpio_setup(&PORTD,&DDRD,MODE,START,COUNT)

#endif // PORTD

