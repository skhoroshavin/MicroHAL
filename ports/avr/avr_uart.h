
#pragma once

#include <avr/io.h>

#define avr_uart_can_send() (UCSR0A & (1 << UDRE0))
#define avr_uart_send(value) do { UDR0 = (value); } while(0)

#define avr_uart_can_recv() (UCSR0A & (1 << RXC0))
#define avr_uart_recv()      UDR0

void avr_uart_init( uint16_t baud );

void avr_uart_send_blocking( uint8_t c );
uint8_t avr_uart_recv_blocking();
