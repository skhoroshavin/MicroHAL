
#pragma once

#include <stdint.h>

#define DEFINE_GPIO_PIN_OUT(NAME,PORT,POS) \
	inline void NAME##_set() { PORT##_set( (1<<POS) ); } \
	inline void NAME##_clr() { PORT##_clr( (1<<POS) ); }
