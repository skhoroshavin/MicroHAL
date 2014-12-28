
#include <platform/flash.h>
#include <utils/string_utils.h>

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

uint8_t str_equalF( const char * str1, flash_str strF )
{
	while( *str1 == flash_read_byte(strF) )
	{
		if( !*str1 ) return 1;
		++str1;
		++strF;
	}
	return 0;
}

uint8_t str_findF( const char * str, flash_ptr strListF, uint8_t stride )
{
	uint8_t i = 0;
	flash_str s = flash_read_ptr(strListF);
	while( s )
	{
		if( str_equalF( str, s ) )
			return i;

		++i;
		strListF = ((uint8_t*)strListF) + stride;
		s = flash_read_ptr(strListF);
	}

	return -1;
}
