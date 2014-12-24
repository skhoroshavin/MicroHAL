
#include "console.h"
#include "microhal.h"

buffered_input_t  _console_input;
buffered_output_t _console_output;

void console_init( uint32_t baud )
{
	input_init( &_console_input );
	output_init( &_console_output );
	uart_console_init( baud );
}

void console_process()
{
	input_process_stream( &_console_input, uart_console, console_on_command );
	output_process_stream( &_console_output, uart_console );
}
