
#pragma once

#include <avr/io.h>

inline void    avr_gpioB_write( uint8_t value ) { PORTB = value;   }
inline uint8_t avr_gpioB_read()                 { return PINB;     }
inline void    avr_gpioB_set( uint8_t value )   { PORTB |= value;  }
inline void    avr_gpioB_clr( uint8_t value )   { PORTB &= ~value; }

void avr_gpioB_setup( uint8_t maskOut, uint8_t maskState );
