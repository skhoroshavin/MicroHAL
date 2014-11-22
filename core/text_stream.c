
#include "text_stream.h"

/***********************************************************************\
 * 8-bit integer conversion                                           *
\***********************************************************************/

static uint8_t decimal_digits8( uint8_t value )
{
	uint8_t p = 10;
	uint8_t i;
	for( i = 1; i < 5; ++i )
	{
		if( value < p )
			return i;
		p *= 10;
	}
	return i;
}

static void divmod10_8( uint8_t value, uint8_t * res, uint8_t * mod )
{
	uint8_t tmp;

	/* Multiply by 0.8 */
	*res = value >> 1;	/* 0.10000000 */
	*res += *res >> 1;  /* 0.11000000 */
	*res += *res >> 4;  /* 0.11001100 */
	tmp = *res;

	/* Divide by 8 */
	*res >>= 3;

	/* Calc remainder */
	*mod = (uint8_t)(value - ((*res << 1) + (tmp & ~((uint8_t)7))) );
	if( *mod > 9 )
	{
		*mod -= 10;
		++(*res);
	}
}

char * write_uint8( char * begin, uint8_t value )
{
	char * end = begin + decimal_digits8(value);
	char * cur = end;
	do
	{
		uint8_t mod;
		divmod10_8( value, &value, &mod );
		*--cur = mod + '0';
	}
	while( value );

	return end;
}

char * write_int8( char * begin, int8_t value )
{
	if( value < 0 )
	{
		*begin++ = '-';
		value = -value;
	}
	return write_int8( begin, value );
}

/***********************************************************************\
 * 16-bit integer conversion                                           *
\***********************************************************************/

static uint8_t decimal_digits16( uint16_t value )
{
	uint16_t p = 10;
	uint8_t i;
	for( i = 1; i < 5; ++i )
	{
		if( value < p )
			return i;
		p *= 10;
	}
	return i;
}

static void divmod10_16( uint16_t value, uint16_t * res, uint8_t * mod )
{
	uint16_t tmp;

	/* Multiply by 0.8 */
	*res = value >> 1;	/* 0.10000000 00000000 */
	*res += *res >> 1;  /* 0.11000000 00000000 */
	*res += *res >> 4;  /* 0.11001100 00000000 */
	*res += *res >> 8;  /* 0.11001100 11001100 */
	tmp = *res;

	/* Divide by 8 */
	*res >>= 3;

	/* Calc remainder */
	*mod = (uint8_t)(value - ((*res << 1) + (tmp & ~((uint16_t)7))) );
	if( *mod > 9 )
	{
		*mod -= 10;
		++(*res);
	}
}

char * write_uint16( char * begin, uint16_t value )
{
	char * end = begin + decimal_digits16(value);
	char * cur = end;
	do
	{
		uint8_t mod;
		divmod10_16( value, &value, &mod );
		*--cur = mod + '0';
	}
	while( value );

	return end;
}

char * write_int16( char * begin, int16_t value )
{
	if( value < 0 )
	{
		*begin++ = '-';
		value = -value;
	}
	return write_int16( begin, value );
}

/***********************************************************************\
 * 32-bit integer conversion                                           *
\***********************************************************************/

static uint8_t decimal_digits32( uint32_t value )
{
	uint32_t p = 10;
	uint8_t i;
	for( i = 1; i < 10; ++i )
	{
		if( value < p )
			return i;
		p *= 10;
	}
	return i;
}

static void divmod10_32( uint32_t value, uint32_t * res, uint8_t * mod )
{
	uint32_t tmp;

	/* Multiply by 0.8 */
	*res = value >> 1;	/* 0.10000000 00000000 00000000 00000000 */
	*res += *res >> 1;  /* 0.11000000 00000000 00000000 00000000 */
	*res += *res >> 4;  /* 0.11001100 00000000 00000000 00000000 */
	*res += *res >> 8;  /* 0.11001100 11001100 00000000 00000000 */
	*res += *res >> 16; /* 0.11001100 11001100 11001100 11001100 */
	tmp = *res;

	/* Divide by 8 */
	*res >>= 3;

	/* Calc remainder */
	*mod = (uint8_t)(value - ((*res << 1) + (tmp & ~((uint32_t)7))) );
	if( *mod > 9 )
	{
		*mod -= 10;
		++(*res);
	}
}

char * write_uint32( char * begin, uint32_t value )
{
	char * end = begin + decimal_digits32(value);
	char * cur = end;
	do
	{
		uint8_t mod;
		divmod10_32( value, &value, &mod );
		*--cur = mod + '0';
	}
	while( value );

	return end;
}

char * write_int32( char * begin, int32_t value )
{
	if( value < 0 )
	{
		*begin++ = '-';
		value = -value;
	}
	return write_int32( begin, value );
}
