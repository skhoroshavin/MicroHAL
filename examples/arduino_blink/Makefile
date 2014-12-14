
PLATFORM = AVR
MCU      = atmega328p
HALDIR   = ../..
TARGET   = blink

SOURCES  = main.c \
	core/list.c \
	core/task_queue.c \
	core/int_to_string.c \
	core/string_utils.c \
	core/text_input.c \
	core/text_output.c \
	core/console.c

include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
#	avr-objdump -d build/$(TARGET)
	avr-size build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
