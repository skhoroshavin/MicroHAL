
#pragma once

#include <core/avr/gpio.h>
#include <core/gpio.h>

DEFINE_GPIO_PIN_OUT(LED, avr_gpioB, 4)

void halInit();
void halProcess();
