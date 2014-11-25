
#pragma once

#include <avr/io.h>

#define AVR_UART(name,index) \
	inline void name##_init( uint32_t baud ) \
	{ \
		UBRR##index    = cpu_freq / 16 / baud - 1; \
		UCSR##index##B = (1 << RXEN0) | (1 << TXEN0); \
	} \
	extern inline uint8_t name##_can_send() { return UCSR##index##A & (1 << UDRE##index); } \
	inline uint8_t name##_can_recv() { return UCSR##index##A & (1 << RXC##index); } \
	extern inline void name##_send( uint8_t value ) { UDR##index = value; } \
	inline uint8_t name##_recv() { return UDR##index; }
