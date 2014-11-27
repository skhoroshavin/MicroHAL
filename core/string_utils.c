
#include <core/string_utils.h>
#include <core/flash.h>

uint8_t str_equal( const char * str1, const char * str2 )
{
	while( *str1 == *str2 )
	{
		if( !*str1 ) return 1;
		++str1;
		++str2;
	}
	return 0;
}

uint8_t str_equalF( const char * str1, const char * strF )
{
	while( *str1 == flash_read_byte(strF) )
	{
		if( !*str1 ) return 1;
		++str1;
		++strF;
	}
	return 0;
}

