
#pragma once

#include <avr/io.h>
#include <core/bit_utils.h>

typedef uint8_t avr_gpio_t;

#define AVR_GPIO_OUTPUT(name,port,pin,size,init) \
	inline void name##_write( avr_gpio_t value ) { MASKED_WRITE(PORT##port,pin,size,value); } \
	inline void name##_init() \
	{ \
		MASKED_WRITE(PORT##port,pin,size,init); \
		MASKED_WRITE(DDR##port, pin,size,0xff); \
	}

#define AVR_GPIO_INPUT(name,port,pin,size,pullup) \
	inline avr_gpio_t name##_read() { return MASKED_READ(PIN##port,pin,size); } \
	inline void name##_init() \
	{ \
		MASKED_WRITE(DDR##port, pin,size, 0); \
		MASKED_WRITE(PORT##port,pin,size, pullup ? 0xff : 0); \
	}

#define AVR_GPIO_OPENDRAIN(name,port,pin,size,init) \
	inline void name##_write( avr_gpio_t value ) { MASKED_WRITE(DDR##port,pin,size,~(value)); } \
	inline avr_gpio_t name##read() { return MASKED_READ(PIN##port,pin,size); } \
	inline void name##_init() \
	{ \
		MASKED_WRITE(PORT##port,pin,size,0); \
		MASKED_WRITE(DDR##port, pin,size,~(init)); \
	}
