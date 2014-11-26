
#include "text_output.h"
#include <core/ring_buffer.h>
#include <core/flash.h>

void output_init( buffered_output_t * out )
{
	rb_init( out );
}

void output_process( buffered_output_t * out )
{
	if( rb_is_empty(out) ) return;
	if( !out->can_send() ) return;

	char tmp;
	output_item_t * item = &rb_front(out);

	switch( item->type )
	{
	case OUTPUT_ITEM_MEM:
		tmp = *item->data;
		if( !tmp )
		{
			rb_pop_front(out);
			return;
		}
		++item->data;
		out->send( tmp );
		return;

	case OUTPUT_ITEM_FLASH:
		tmp = flash_read_byte(item->data);
		if( !tmp )
		{
			rb_pop_front(out);
			return;
		}
		++item->data;
		out->send( tmp );
		return;
	}
}

uint8_t output_send_mem_str( buffered_output_t * out, const char * msg )
{
	output_item_t item =
	{
		.type = OUTPUT_ITEM_MEM,
		.data = msg
	};

	uint8_t res = out->end;
	rb_push_back( out, item );
	return res;
}

uint8_t output_send_flash_str( buffered_output_t * out, const char * msg )
{
	output_item_t item =
	{
		.type = OUTPUT_ITEM_FLASH,
		.data = msg
	};

	uint8_t res = out->end;
	rb_push_back( out, item );
	return res;
}

