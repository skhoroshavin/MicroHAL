
#include "string_utils.h"

inline static void divmodu10( uint32_t value, uint32_t * res, uint8_t * mod )
{
	uint32_t tmp;

	// Multiply by 0.8
	*res = value >> 1;
	*res += *res >> 1;
	*res += *res >> 4;
	*res += *res >> 8;
	*res += *res >> 16;
	tmp = *res;

	// Divide by 8
	*res >>= 3;

	// Calc remainder
	*mod = (uint8_t)(value - ((*res << 1) + (tmp & ~((uint32_t)7))) );
	if( *mod > 9 )
	{
		*mod -= 10;
		++(*res);
	}
}

char * uint32_to_string( uint32_t value, char * buf )
{
	buf += 11;
	*--buf = 0;
	do
	{
		uint32_t res;
		uint8_t mod;

		divmodu10( value, &res, &mod );
		*--buf = mod + '0';
		value = res;
	}
	while( value );

	return buf;
}
