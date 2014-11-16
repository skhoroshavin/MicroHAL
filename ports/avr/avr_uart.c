
#include "avr_uart.h"

void avr_uart_init( uint16_t baud )
{
	UBRR0 = 1000000 / baud - 1;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void avr_uart_send_blocking(uint8_t c )
{
	while( !avr_uart_can_send() );
	avr_uart_send(c);
}

uint8_t avr_uart_recv_blocking()
{
	while( !avr_uart_can_recv() );
	return avr_uart_recv();
}
