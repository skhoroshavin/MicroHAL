
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -std=c99 -flto -Os -Wall -DAVR -I. -I$(HALDIR)
LDFLAGS = -mmcu=$(MCU) -std=c99 -flto -Os
