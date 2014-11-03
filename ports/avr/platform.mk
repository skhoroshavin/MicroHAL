
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -flto -O3 -std=c99 -I. -I$(HALDIR)
LDFLAGS = -mmcu=$(MCU) -flto -O3
