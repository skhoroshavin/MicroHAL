
#pragma once

#include <avr/io.h>

#define avr_uart_send(value) do { UDR0 = (value); } while(0)
#define avr_uart_recv()      UDR0

#define avr_uart_can_send() (UCSR0A & (1 << UDRE0))
#define avr_uart_has_data() (UCSR0A & (1 << RXC0))

void avr_uart_init( uint16_t baud );
