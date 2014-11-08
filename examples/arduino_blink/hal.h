
#pragma once

#include <ports/avr/gpio.h>
#include <ports/avr/basic_timer.h>
#include <ports/avr/advanced_timer.h>

#define LED     avr_gpio_b, 5

#define MAIN_TIMER avr_advanced_timer

void halInit();
void halProcess();
