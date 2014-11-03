
#pragma once

#include <stdint.h>

#define DEFINE_GPIO_PIN_OUT(NAME,GPIO,PIN) \
	inline void NAME##_set() { GPIO##_set( (1<<PIN) ); } \
	inline void NAME##_clr() { GPIO##_clr( (1<<PIN) ); } \
	inline void NAME##_write( uint8_t value ) { if(value) NAME##_set(); else NAME##_clr(); }

#define DEFINE_GPIO_PIN_IN(NAME,GPIO,PIN) \
	inline uint8_t NAME##_read() { return (GPIO##_read() >> PIN) & 0x1; }
