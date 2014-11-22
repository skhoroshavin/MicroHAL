
#pragma once

#include <stdint.h>

char * write_uint8( char * begin, uint8_t value );
char * write_int8( char * begin, int8_t value );

char * write_uint16( char * begin, uint16_t value );
char * write_int16( char * begin, int16_t value );

char * write_uint32( char * begin, uint32_t value );
char * write_int32( char * begin, int32_t value );
