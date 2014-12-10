
#include "text_input.h"
#include <core/buffer.h>
#include <core/int_to_string.h>

void input_init( buffered_input_t * in )
{
	buf_init( &in->data );
	buf_init( &in->argv );
}

uint8_t input_process_char( buffered_input_t * in, char c )
{
	if( c == ' ' )
	{
		if( buf_is_empty( &in->data ) )
			return 0;

		if( buf_back( &in->data ) )
			buf_push_back( &in->data, 0 );
	}
	else if( (c == '\n') || (c == '\r') )
	{
		if( buf_is_empty( &in->data ) )
			return 0;

		if( buf_back( &in->data ) )
			buf_push_back( &in->data, 0 );

		return 1;
	}
	else
	{
		if( buf_is_empty( &in->data ) || !buf_back( &in->data ) )
			buf_push_back( &in->argv, in->data.data + in->data.size );
		buf_push_back( &in->data, c );
	}

	return 0;
}
