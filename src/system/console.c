
#include "console.h"
#include <system/soft_irq.h>

buffered_input_t  _console_input;
buffered_output_t _console_output;

void console_init( uint32_t baud )
{
	input_init( &_console_input );
	output_init( &_console_output );
	console_uart_init( baud );

	soft_irq_raise( console_soft_irq_id );
}

void console_process()
{
	input_process_stream( &_console_input, console_uart, console_on_command );
	output_process_stream( &_console_output, console_uart );

	soft_irq_raise( console_soft_irq_id );
}
