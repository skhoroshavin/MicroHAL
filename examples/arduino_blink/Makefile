
HALDIR  = ../..
TARGET  = blink
SOURCES = \
	main.c \
	microhal.c \
	ports/avr/avr_uart.c

MCU   = atmega328p
include $(HALDIR)/ports/avr/build.mk
include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
