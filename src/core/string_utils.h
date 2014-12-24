
#pragma once

#include <core/flash.h>

uint8_t str_equal( const char * str1, const char * str2 );
uint8_t str_equalF( const char * str1, flash_str strF );

uint8_t str_findF( const char * str, flash_ptr strListF, uint8_t stride );
