
#pragma once

#include <core/ring_buffer.h>

typedef enum
{
	OUTPUT_ITEM_MEM,
	OUTPUT_ITEM_FLASH
} output_item_type_t;

typedef struct
{
	output_item_type_t type;
	const char *       data;
} output_item_t;

typedef struct
{
	DECLARE_RING_BUFFER(buffer,output_item_t,8);
} buffered_output_t;

void output_init( buffered_output_t * out );
uint8_t output_send_mem_str( buffered_output_t * out, const char * msg );
uint8_t output_send_flash_str( buffered_output_t * out, const char * msg );

uint8_t output_process_char( buffered_output_t * out );

#define output_process_stream(out,stream) \
	do \
	{ \
		char tmp; \
		while( stream##_can_send() && (tmp = output_process_char( out )) ) \
			stream##_send( tmp ); \
	} while(0)
