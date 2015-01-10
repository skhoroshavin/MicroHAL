
#pragma once

#include <stddef.h>

#define _CAT(a,b) a##b
#define CAT(a,b)  _CAT(a,b)

#define STATIC_ASSERT(pred,name) typedef char CAT(assertion_failed_##name##_,__LINE__)[2*(pred)-1]

/**
 * @brief Get number of elements in fixed sized array
 * @param a Pointer to array
 * @return Number of elements in array
 */
#define array_size(a) (sizeof(a)/sizeof((a)[0]))

/**
 * @brief Get pointer to parent structure
 * @param ptr Pointer to member of structure
 * @param type Type of parent structure
 * @param member Name of parent structure member
 * @return Pointer to parent structure
 */
#define container_of(ptr,type,member) ((type*)((char*)(ptr)-offsetof(type,member)))

/**
 * @brief Swap two values
 * @param type Type of values
 * @param a First value to swap
 * @param b Second value to swap
 */
#define swap(type, a, b) \
	do { type tmp = a; a = b; b = tmp; } while(0)

/**
 * @brief Bubble sort small array (<256 elements)
 * @param type Type of values
 * @param data Array data
 * @param size Array size
 * @param less Array elements comparator
 */
#define sort_bubble(type, data, size, less) \
	do \
	{ \
		uint8_t i, j; \
		for( i = 0; i < (size); ++i ) \
		{ \
			for( j = i+1; j < (size); ++j ) \
			{ \
				if( less( data[j], data[i] ) ) \
					swap( type, data[i], data[j] ); \
			} \
		} \
	} while(0)
