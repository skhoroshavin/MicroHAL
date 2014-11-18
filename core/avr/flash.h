
#pragma once

#include <avr/pgmspace.h>

#define FLASH PROGMEM

inline uint8_t flash_read_byte( const void * pPtr ) { return pgm_read_byte(pPtr); }
