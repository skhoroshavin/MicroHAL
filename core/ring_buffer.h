
#pragma once

#define DEFINE_FIXED_RING_BUFFER(name,type,order) \
	enum { name##_max_size = (1 << order)-1 }; \
	typedef struct \
	{ \
		uint8_t begin; \
		uint8_t end; \
		type    data[name##_max_size]; \
	} name##_t; \
	inline void name##_init( name##_t * buf ) { buf->begin = buf->end = 0; } \
	inline uint8_t name##_is_empty( name##_t * buf ) { return (buf->begin == buf->end); } \
	inline uint8_t name##_size( name##_t * buf ) { return (buf->end - buf->begin) & name##_max_size; } \
	inline type    name##_front( name##_t * buf ) { return buf->data[buf->begin]; } \
	inline type    name##_back( name##_t * buf ) { return buf->data[(buf->end-1) & name##_max_size]; } \
	inline void name##_push_front( name##_t * buf, type value ) \
	{ \
		buf->data[buf->begin] = value; \
		--buf->begin; buf->begin = buf->begin & name##_max_size; \
	} \
	inline void name##_push_back( name##_t * buf, type value ) \
	{ \
		buf->data[buf->end] = value; \
		++buf->end; buf->end = buf->end & name##_max_size; \
	} \
	inline void name##_pop_front( name##_t * buf ) { ++buf->begin; buf->begin = buf->begin & name##_max_size; } \
	inline void name##_pop_back( name##_t * buf ) { --buf->end; buf->end = buf->end & name##_max_size; }
