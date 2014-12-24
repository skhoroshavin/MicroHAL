
#pragma once

typedef const char * flash_str;
typedef const void * flash_ptr;

#ifdef AVR

#include <avr/pgmspace.h>

#define FLASH_STR(name) const char name[] PROGMEM
#define FLASH_DATA(type,name) const type name[] PROGMEM

inline uint8_t  flash_read_byte( flash_ptr pPtr )  { return pgm_read_byte(pPtr);  }
inline uint16_t flash_read_word( flash_ptr pPtr )  { return pgm_read_word(pPtr);  }
inline uint32_t flash_read_dword( flash_ptr pPtr ) { return pgm_read_dword(pPtr); }
inline float    flash_read_float( flash_ptr pPtr ) { return pgm_read_float(pPtr); }
inline void *   flash_read_ptr( flash_ptr pPtr )   { return pgm_read_ptr(pPtr);   }

#else /* AVR */

#define FLASH_STR(name) const char name[]
#define FLASH_DATA(type,name) const type name[]

inline uint8_t  flash_read_byte( flash_ptr pPtr )  { return *((uint8_t*)pPtr);  }
inline uint16_t flash_read_word( flash_ptr pPtr )  { return *((uint16_t*)pPtr);  }
inline uint32_t flash_read_dword( flash_ptr pPtr ) { return *((uint32_t*)pPtr); }
inline float    flash_read_float( flash_ptr pPtr ) { return *((float*)pPtr); }
inline void *   flash_read_ptr( flash_ptr pPtr )   { return *((void**)pPtr);   }

#endif /* AVR */
