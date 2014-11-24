
#include "microhal.h"
#include <core/flash.h>
#include <core/text_stream.h>
#include <core/buffer.h>

enum
{
	tick_period_ms   = 4000,
	sys_clock_period = (uint32_t)sys_clock_freq*tick_period_ms/1000
};

STATIC_ASSERT(sys_clock_period < 0x10000, main);

void send_msg( const char * pMessage )
{
	while( *pMessage )
	{
		while( !debug_can_send() );
		debug_send(*pMessage);
		++pMessage;
	}
}

void send_msg_flash( const char * pMessage )
{
	char c = flash_read_byte(pMessage);
	while( c )
	{
		while( !debug_can_send() );
		debug_send( c );

		++pMessage;
		c = flash_read_byte(pMessage);
	}
}

const char g_pMsgOn[]   FLASH = "LED is on!\n\r";
const char g_pMsgOff[]  FLASH = "LED is off!\n\r";
const char g_pMsgSize[] FLASH = "Size: ";
const char g_pMsgRecv[] FLASH = "Message: ";

struct
{
	uint8_t size;
	char    data[32];
} buffer;

void process_uart()
{
	while( debug_can_recv() )
	{
		char c = debug_recv();
		buf_push_back( &buffer, c );
	}
}

int main(void)
{
	uint8_t  led_state   = 0;
	uint8_t  last_tick   = 0;
	uint16_t accumulator = 0;
	const char * pMsg = g_pMsgOff;
	char     buf[32];

	led_init();
	sys_clock_init();
	debug_init( 9600 );
	buf_init( &buffer );

	for(;;)
	{
		process_uart();

		uint8_t cur_tick = sys_clock_value();
		accumulator += (uint8_t)(cur_tick - last_tick);
		last_tick = cur_tick;

		if( accumulator > sys_clock_period )
		{
			accumulator -= sys_clock_period;

			led_state = 1 - led_state;
			pMsg = led_state ? g_pMsgOn : g_pMsgOff;

			led_write( led_state );
			send_msg_flash( pMsg );

			send_msg_flash( g_pMsgSize );
			*write_uint16( buf, buf_size( &buffer ) ) = 0;
			send_msg( buf );
			send_msg( "\n\r" );

			send_msg_flash( g_pMsgRecv );
			buf_push_back( &buffer, 0 );
			send_msg( buffer.data );
			buf_clear( &buffer );
			send_msg( "\n\r" );
		}
	}

	return 0;
}
