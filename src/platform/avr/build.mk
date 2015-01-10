
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -std=c99 -flto -O2 -Wall -DAVR -I. -I$(OSDIR)
LDFLAGS = -mmcu=$(MCU) -std=c99 -flto -O2
