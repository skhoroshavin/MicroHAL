
#pragma once

#include <avr/pgmspace.h>

#define FLASH PROGMEM

inline uint8_t  flash_read_byte( const void * pPtr )  { return pgm_read_byte(pPtr);  }
inline uint16_t flash_read_word( const void * pPtr )  { return pgm_read_word(pPtr);  }
inline uint32_t flash_read_dword( const void * pPtr ) { return pgm_read_dword(pPtr); }
inline float    flash_read_float( const void * pPtr ) { return pgm_read_float(pPtr); }
inline void *   flash_read_ptr( const void * pPtr )   { return pgm_read_ptr(pPtr);   }
