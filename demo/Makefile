
PLATFORM = AVR
MCU      = atmega328p
OSDIR   = ../src
TARGET   = blink

INCLUDES = -Iarduino

SOURCES  = main.c \
	arduino/hal.c \
	core/list.c \
	core/int_to_string.c \
	core/string_utils.c \
	core/text_input.c \
	core/text_output.c \
	system/console.c \
	system/scheduler.c

include $(OSDIR)/core/build.mk

flash: build/$(TARGET)
#	avr-objdump -d build/$(TARGET)
	avr-size build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
