
#pragma once

#include <avr/io.h>

void avr_uart_init( uint16_t baud );
void avr_uart_send_blocking( uint8_t c );
uint8_t avr_uart_recv_blocking();

#define AVR_UART(name) \
	inline void name##_init( uint32_t baud ) { avr_uart_init( baud ); } \
	inline void name##_send_byte( uint8_t value ) { avr_uart_send_blocking(value); } \
	inline uint8_t name##_recv_byte() { return avr_uart_recv_blocking(); }
