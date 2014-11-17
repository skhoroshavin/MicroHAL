
#include <microhal.h>

#define avr_uart_can_send() (UCSR0A & (1 << UDRE0))
#define avr_uart_send(value) do { UDR0 = (value); } while(0)

#define avr_uart_can_recv() (UCSR0A & (1 << RXC0))
#define avr_uart_recv()      UDR0

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
