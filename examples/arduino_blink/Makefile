
PLATFORM = AVR
MCU      = atmega328p
HALDIR   = ../..
TARGET   = blink
SOURCES  = main.c core/text_stream.c core/buffered_output.c

include $(HALDIR)/core/build.mk

flash: build/$(TARGET)
#	avr-size build/$(TARGET)
	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
