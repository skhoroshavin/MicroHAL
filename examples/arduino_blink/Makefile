
PLATFORM = AVR
MCU      = atmega328p
HALDIR   = ../..
TARGET   = blink
SOURCES  = \
	main.c \
	ports/avr/avr_uart.c

include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
