
#include "avr_uart.h"

void avr_uart_init( uint16_t baud )
{
	UBRR0 = 1000000 / baud - 1;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}
