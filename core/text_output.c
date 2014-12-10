
#include "text_output.h"
#include <core/ring_buffer.h>
#include <core/flash.h>

void output_init( buffered_output_t * out )
{
	rb_init( &out->buffer );
}

uint8_t output_send_mem_str( buffered_output_t * out, const char * msg )
{
	output_item_t item =
	{
		.type = OUTPUT_ITEM_MEM,
		.data = msg
	};

	uint8_t res = out->buffer.end;
	rb_push_back( &out->buffer, item );
	return res;
}

uint8_t output_send_flash_str( buffered_output_t * out, const char * msg )
{
	output_item_t item =
	{
		.type = OUTPUT_ITEM_FLASH,
		.data = msg
	};

	uint8_t res = out->buffer.end;
	rb_push_back( &out->buffer, item );
	return res;
}

uint8_t output_process_char( buffered_output_t * out )
{
	if( rb_is_empty(&out->buffer) ) return 0;

	char tmp;
	output_item_t * item = &rb_front(&out->buffer);

	switch( item->type )
	{
	case OUTPUT_ITEM_MEM:
		tmp = *item->data;
		if( !tmp )
		{
			rb_pop_front(&out->buffer);
			return 0;
		}
		++item->data;
		return tmp;

	case OUTPUT_ITEM_FLASH:
		tmp = flash_read_byte(item->data);
		if( !tmp )
		{
			rb_pop_front(&out->buffer);
			return 0;
		}
		++item->data;
		return tmp;
	}

	return 0;
}
