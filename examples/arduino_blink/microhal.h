
#pragma once

#include <ports/avr/gpio.h>
#include <ports/avr/basic_timer.h>
#include <ports/avr/advanced_timer.h>
#include <ports/avr/avr_uart.h>

AVR_GPIO_OUTPUT(led, B,5,1, 0)

#define MAIN_TIMER avr_advanced_timer

void halInit();
void halProcess();
