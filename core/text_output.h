
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
	void (*send)( uint8_t );
	uint8_t (*can_send)();

	DECLARE_RING_BUFFER(buffer,output_item_t,16);
} buffered_output_t;

void output_init( buffered_output_t * out );
void output_process( buffered_output_t * out );
uint8_t output_send_mem_str( buffered_output_t * out, const char * msg );
uint8_t output_send_flash_str( buffered_output_t * out, const char * msg );
