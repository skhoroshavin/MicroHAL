
#pragma once

#include <stdint.h>
#include "pp_utils.h"

/***********************************************************************\
 * Ring buffer initialization                                          *
\***********************************************************************/

#define rb_init(rb)      do { (rb)->begin = (rb)->end = 0; } while(0)

/***********************************************************************\
 * Ring buffer queries                                                 *
\***********************************************************************/

#define rb_is_empty(rb)  ((rb)->begin == (rb)->end)
#define rb_pos(rb,pos)   ((uint8_t)(pos) % ARRAY_SIZE((rb)->data))
#define rb_size(rb)      rb_pos(rb,(rb)->end - (rb)->begin)
#define rb_front(rb)     ((rb)->data[(rb)->begin])
#define rb_back(rb)      ((rb)->data[rb_pos(rb,(rb)->end - 1)])

/***********************************************************************\
 * Ring buffer modification                                            *
\***********************************************************************/

#define rb_push_front(rb,value) do { \
		(rb)->begin = rb_pos(rb,(rb)->begin-1); \
		(rb)->data[(rb)->begin] = value; \
	} while(0)
#define rb_push_back(rb,value) do { \
		(rb)->data[(rb)->end] = value; \
		(rb)->end = rb_pos(rb,(rb)->end+1); \
	} while(0)

#define rb_pop_front(rb) do { (rb)->begin = rb_pos(rb,(rb)->begin+1); } while(0)
#define rb_pop_back(rb) do { (rb)->end= rb_pos(rb,(rb)->end-1); } while(0)
