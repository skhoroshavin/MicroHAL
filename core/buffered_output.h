
#pragma once

#include <stdint.h>

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

	uint8_t begin;
	uint8_t end;
	output_item_t data[16];
} buffered_output_t;

void output_init( buffered_output_t * out );
void output_process( buffered_output_t * out );
uint8_t output_send_mem_str( buffered_output_t * out, const char * msg );
uint8_t output_send_flash_str( buffered_output_t * out, const char * msg );
