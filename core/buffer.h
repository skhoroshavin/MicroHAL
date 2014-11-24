
#pragma once

/***********************************************************************\
 * Buffer initialization                                               *
\***********************************************************************/

#define buf_init(buf)     do { (buf)->size = 0; } while(0)

/***********************************************************************\
 * Buffer queries                                                      *
\***********************************************************************/

#define buf_is_empty(buf) (!(buf)->size)
#define buf_size(buf)     ((buf)->size)
#define buf_front(buf)    ((buf)->data[0])
#define buf_back(buf)     ((buf)->data[(buf)->size-1])
#define buf_value(buf,i)  ((buf)->data[i])

/***********************************************************************\
 * Buffer modification                                                 *
\***********************************************************************/

#define buf_push_back(buf,value) do { (buf)->data[(buf)->size] = value; ++(buf)->size; } while(0)
#define buf_pop_back(buf) do { --(buf)->size; } while(0)
#define buf_clear(buf) do { (buf)->size = 0; } while(0)
