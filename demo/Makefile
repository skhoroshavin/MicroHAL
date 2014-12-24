
PLATFORM = AVR
MCU      = atmega328p
HALDIR   = ../src
TARGET   = blink

INCLUDES = -Iarduino

SOURCES  = main.c \
	core/list.c \
	core/int_to_string.c \
	core/string_utils.c \
	core/text_input.c \
	core/text_output.c \
	core/scheduler.c \
	core/console.c

include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
#	avr-objdump -d build/$(TARGET)
	avr-size build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
