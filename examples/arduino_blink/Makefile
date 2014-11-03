
HALDIR  = ../..
TARGET  = blink
SOURCES = main.c hal.c core/avr/gpio.c

MCU   = atmega328p
include $(HALDIR)/core/avr/platform.mk
include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
	sudo avrdude -c arduino -P /dev/ttyUSB0 -p m328p -U flash:w:$<:e
