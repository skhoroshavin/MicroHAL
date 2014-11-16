
#pragma once

#include <avr/io.h>
#include <core/bit_utils.h>

#define AVR_GPIO_OUTPUT(name,port,pin,size,init) \
	inline void name##_write( uint8_t value ) { MASKED_WRITE(PORT##port,pin,size,value); } \
	inline void name##_init() \
	{ \
		MASKED_WRITE(PORT##port,pin,size,init); \
		MASKED_WRITE(DDR##port, pin,size,MASK(size)); \
	}

#define AVR_GPIO_INPUT(name,port,pin,size,pullup) \
	inline uint8_t name##_read() { return (PIN##port >> (pin)) & MASK(size); } \
	inline void name##_init() \
	{ \
		MASKED_WRITE(DDR##port, pin,size, 0); \
		MASKED_WRITE(PORT##port,pin,size, pullup ? MASK(size) : 0); \
	}
