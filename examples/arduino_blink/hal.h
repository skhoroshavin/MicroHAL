
#pragma once

#include <ports/avr/gpio.h>
#include <ports/avr/basic_timer.h>

DEFINE_GPIO_PIN_OUT(LED, avr_gpioB, 5)

void halInit();
void halProcess();
