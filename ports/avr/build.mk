
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -std=c99 -flto -O3 -Wall -I$(HALDIR)
LDFLAGS = -mmcu=$(MCU) -std=c99 -flto -O3
