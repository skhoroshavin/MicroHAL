
#pragma once

#define MASK(size) ((1 << (size))-1)

#define MASKED_WRITE(reg,offset,size,value) \
	do { \
		if( size > 1 ) \
		{ \
			reg = ( reg & ~(MASK(size) << (offset)) ) | \
				  ( (value) << (offset) ); \
		} \
		else \
		{ \
			if(value) reg |= 1 << (offset); \
			else reg &= ~(1 << (offset)); \
		} \
	} while(0)
