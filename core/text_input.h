
#pragma once

#include <core/buffer.h>

typedef struct
{
	uint8_t (*recv)();
	uint8_t (*can_recv)();
	void (*process)( uint8_t argc, const char * argv[] );

	DECLARE_BUFFER(data, char,        32);
	DECLARE_BUFFER(argv, const char*,  8);
} buffered_input_t;

void input_init( buffered_input_t * in );
void input_process( buffered_input_t * in );
