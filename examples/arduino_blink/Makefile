
HALDIR  = ../..
TARGET  = blink
SOURCES = \
	main.c \
	hal.c \
	ports/avr/gpio.c \
	ports/avr/basic_timer.c

MCU   = atmega328p
include $(HALDIR)/ports/avr/platform.mk
include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
	sudo avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
