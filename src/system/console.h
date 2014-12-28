
#pragma once

#include <utils/text_input.h>
#include <utils/text_output.h>

#include "hal.h"

extern buffered_input_t  _console_input;
extern buffered_output_t _console_output;

void console_init( uint32_t baud );
void console_process();

#define console_print(...) output_send_flash_str(&_console_output,__VA_ARGS__)

extern void console_on_command( uint8_t argc, const char * argv[] );
