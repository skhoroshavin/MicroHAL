
PLATFORM = AVR
MCU      = atmega328p
OSDIR   = ../src
TARGET   = demo

INCLUDES = -Iarduino

SOURCES  = main.c \
	arduino/hal.c \
	utils/string_utils.c \
	utils/text_input.c \
	utils/text_output.c \
	system/console.c \
	system/soft_irq.c \
	system/scheduler.c

include $(OSDIR)/platform/build.mk

flash: build/$(TARGET)
#	avr-objdump -d build/$(TARGET)
	avr-size build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
