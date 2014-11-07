
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
	AVR_GPIO_OUTPUT_HIGH    = _AVR_OUTPUT | _AVR_HIGH
} avr_gpio_mode_t;

void avr_gpio_setup( volatile uint8_t * portReg, volatile uint8_t * ddrReg,
					 avr_gpio_mode_t mode, uint8_t start, uint8_t count );

#ifdef PORTA
#define avr_gpio_a_write(VALUE)            do { PORTA = VALUE; } while(0)
#define avr_gpio_a_set(VALUE)              do { PORTA |= (VALUE); } while(0)
#define avr_gpio_a_clear(VALUE)            do { PORTA &= ~(VALUE); } while(0)
#define avr_gpio_a_masked_set(MASK,VALUE)  do { PORTA = (PORTA & ~(MASK)) | (VALUE); }
#define avr_gpio_a_read()                  (PINA)
#define avr_gpio_a_setup(MODE,START,COUNT) avr_gpio_setup(&PORTA,&DDRA,MODE,START,COUNT)
#endif // PORTA

#ifdef PORTB
#define avr_gpio_b_write(VALUE)            do { PORTB = VALUE; } while(0)
#define avr_gpio_b_set(VALUE)              do { PORTB |= (VALUE); } while(0)
#define avr_gpio_b_clear(VALUE)            do { PORTB &= ~(VALUE); } while(0)
#define avr_gpio_b_masked_set(MASK,VALUE)  do { PORTB = (PORTB & ~(MASK)) | (VALUE); }
#define avr_gpio_b_read()                  (PINB)
#define avr_gpio_b_setup(MODE,START,COUNT) avr_gpio_setup(&PORTB,&DDRB,MODE,START,COUNT)
#endif // PORTB

#ifdef PORTC
#define avr_gpio_c_write(VALUE)            do { PORTC = VALUE; } while(0)
#define avr_gpio_c_set(VALUE)              do { PORTC |= (VALUE); } while(0)
#define avr_gpio_c_clear(VALUE)            do { PORTC &= ~(VALUE); } while(0)
#define avr_gpio_c_masked_set(MASK,VALUE)  do { PORTC = (PORTC & ~(MASK)) | (VALUE); }
#define avr_gpio_c_read()                  (PINC)
#define avr_gpio_c_setup(MODE,START,COUNT) avr_gpio_setup(&PORTC,&DDRC,MODE,START,COUNT)
#endif // PORTC

#ifdef PORTD
#define avr_gpio_d_write(VALUE)            do { PORTD = VALUE; } while(0)
#define avr_gpio_d_set(VALUE)              do { PORTD |= (VALUE); } while(0)
#define avr_gpio_d_clear(VALUE)            do { PORTD &= ~(VALUE); } while(0)
#define avr_gpio_d_masked_set(MASK,VALUE)  do { PORTD = (PORTD & ~(MASK)) | (VALUE); }
#define avr_gpio_d_read()                  (PIND)
#define avr_gpio_d_setup(MODE,START,COUNT) avr_gpio_setup(&PORTD,&DDRD,MODE,START,COUNT)
#endif // PORTD

#ifdef PORTE
#define avr_gpio_e_write(VALUE)            do { PORTE = VALUE; } while(0)
#define avr_gpio_e_set(VALUE)              do { PORTE |= (VALUE); } while(0)
#define avr_gpio_e_clear(VALUE)            do { PORTE &= ~(VALUE); } while(0)
#define avr_gpio_e_masked_set(MASK,VALUE)  do { PORTE = (PORTE & ~(MASK)) | (VALUE); }
#define avr_gpio_e_read()                  (PINE)
#define avr_gpio_e_setup(MODE,START,COUNT) avr_gpio_setup(&PORTE,&DDRE,MODE,START,COUNT)
#endif // PORTE

#ifdef PORTF
#define avr_gpio_f_write(VALUE)            do { PORTF = VALUE; } while(0)
#define avr_gpio_f_set(VALUE)              do { PORTF |= (VALUE); } while(0)
#define avr_gpio_f_clear(VALUE)            do { PORTF &= ~(VALUE); } while(0)
#define avr_gpio_f_masked_set(MASK,VALUE)  do { PORTF = (PORTF & ~(MASK)) | (VALUE); }
#define avr_gpio_f_read()                  (PINF)
#define avr_gpio_f_setup(MODE,START,COUNT) avr_gpio_setup(&PORTF,&DDRF,MODE,START,COUNT)
#endif // PORTF
