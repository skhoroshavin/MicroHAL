
#pragma once

#include <ports/avr/gpio.h>
#include <ports/avr/basic_timer.h>

#define LED avr_gpioB, 5

#define MAIN_TIMER avr_basic_timer

void halInit();
void halProcess();
