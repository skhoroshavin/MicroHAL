
#pragma once

#include <stdint.h>
#include <core/pp_utils.h>

/***********************************************************************\
 * Buffer declaration                                                  *
\***********************************************************************/

#define DECLARE_BUFFER(name,type,max_size) \
	struct \
	{ \
		uint8_t size; \
		type    data[max_size]; \
	} name

/***********************************************************************\
 * Buffer initialization                                               *
\***********************************************************************/

#define buf_init(buf)     do { (buf)->size = 0; } while(0)

/***********************************************************************\
 * Buffer queries                                                      *
\***********************************************************************/

#define buf_is_empty(buf) (!(buf)->size)
#define buf_is_full(buf)  ((buf)->size == ARRAY_SIZE((buf)->data))
#define buf_size(buf)     ((buf)->size)
#define buf_front(buf)    ((buf)->data[0])
#define buf_back(buf)     ((buf)->data[(buf)->size-1])
#define buf_value(buf,i)  ((buf)->data[i])

/***********************************************************************\
 * Buffer modification                                                 *
\***********************************************************************/

#define buf_push_back_unsafe(buf,value) do { (buf)->data[(buf)->size] = value; ++(buf)->size; } while(0)
#define buf_pop_back_unsafe(buf) do { --(buf)->size; } while(0)
#define buf_push_back(buf,value) do { if( !buf_is_full(buf) ) buf_push_back_unsafe(buf,value); } while(0)
#define buf_pop_back(buf) do { if( !buf_is_empty(buf) ) buf_pop_back_unsafe(buf); } while(0)
#define buf_clear(buf) do { (buf)->size = 0; } while(0)
