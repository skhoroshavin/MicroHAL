
#include "text_input.h"
#include <core/buffer.h>
#include <core/int_to_string.h>

void input_init( buffered_input_t * in )
{
	buf_init( &in->data );
	buf_init( &in->argv );
}

void input_process( buffered_input_t * in )
{
	while( in->can_recv() )
	{
		char tmp = in->recv();

		if( tmp == ' ' )
		{
			if( buf_is_empty( &in->data ) )
				continue;

			if( buf_back( &in->data ) )
				buf_push_back( &in->data, 0 );
		}
		else if( (tmp == '\n') || (tmp == '\r') )
		{
			if( buf_is_empty( &in->data ) )
				continue;

			if( buf_back( &in->data ) )
				buf_push_back( &in->data, 0 );

			in->process( in->argv.size, in->argv.data );
			buf_clear( &in->data );
			buf_clear( &in->argv );
		}
		else
		{
			if( buf_is_empty( &in->data ) || !buf_back( &in->data ) )
				buf_push_back( &in->argv, in->data.data + in->data.size );
			buf_push_back( &in->data, tmp );
		}
	}
}
