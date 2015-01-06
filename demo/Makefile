
PLATFORM = AVR
MCU      = atmega168p
OSDIR   = ../src
TARGET   = demo

INCLUDES = -Ipinboard-atmega168

SOURCES  = main.c \
	pinboard-atmega168/hal.c \
	utils/string_utils.c \
	utils/text_input.c \
	utils/text_output.c \
	system/console.c \
	system/soft_irq.c \
	system/clock.c

include $(OSDIR)/platform/build.mk

flash: build/$(TARGET)
#	avr-objdump -d build/$(TARGET)
	avr-size build/$(TARGET)
	avrdude -c avrftdi -b 57600 -p m168p -P /dev/ttyUSB0 -u -U $<
#	avrdude -c arduino -b 57600 -p m328p -P /dev/ttyUSB0 -u -U $<
