
#pragma once

#define size 16
#define type uint8_t

typedef struct
{
	type    data[size];
	uint8_t begin;
	uint8_t end;
} ring_buffer_t;

inline void ring_buffer_init( ring_buffer_t * pBuffer )
{
	pBuffer->begin = 0;
	pBuffer->end = 0;
}

inline uint8_t ring_buffer_is_empty( ring_buffer_t * pBuffer ) { return (pBuffer->begin == pBuffer->end); }
inline uint8_t ring_buffer_size( ring_buffer_t * pBuffer ) { return (pBuffer->end - pBuffer->begin) % size; }
inline type    ring_buffer_front( ring_buffer_t * pBuffer ) { return pBuffer->data[pBuffer->begin]; }
inline type    ring_buffer_back( ring_buffer_t * pBuffer ) { return pBuffer->data[pBuffer->end]; }

inline void ring_buffer_push_back( ring_buffer_t * pBuffer, type value )
{
	pBuffer->data[pBuffer->end] = value;
	++pBuffer->end;
	pBuffer->end = pBuffer->end % size;
}

inline void ring_buffer_pop_front( ring_buffer_t * pBuffer )
{
	++pBuffer->begin;
	pBuffer->begin = pBuffer->begin % size;
}
