
#pragma once

#include <core/buffer.h>

typedef struct
{
	DECLARE_BUFFER(data, char,        32);
	DECLARE_BUFFER(argv, const char*,  8);
} buffered_input_t;

void input_init( buffered_input_t * in );

uint8_t input_process_char( buffered_input_t * in, char c );

#define input_process_stream(in,stream,handler) \
	while( stream##_can_recv() ) \
	{ \
		if( input_process_char( (in), stream##_recv() ) ) \
		{ \
			handler( (in)->argv.size, (in)->argv.data ); \
			buf_clear( &(in)->data ); \
			buf_clear( &(in)->argv ); \
		} \
	}
