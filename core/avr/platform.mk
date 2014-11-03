
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -flto -O3 -std=c99 -I. -I$(SRCDIR)
LDFLAGS = -mmcu=$(MCU) -flto -O3

