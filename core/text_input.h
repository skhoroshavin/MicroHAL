
#pragma once

#include <core/buffer.h>

#ifndef TEXT_INPUT_BUF_SIZE
#define TEXT_INPUT_BUF_SIZE 32
#endif /* TEXT_INPUT_BUF_SIZE */

#ifndef TEXT_INPUT_MAX_PARAMS
#define TEXT_INPUT_MAX_PARAMS 4
#endif /* TEXT_INPUT_MAX_PARAMS */

typedef struct
{
	DECLARE_BUFFER(data, char,        TEXT_INPUT_BUF_SIZE);
	DECLARE_BUFFER(argv, const char*, TEXT_INPUT_MAX_PARAMS);
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
