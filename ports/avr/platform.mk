
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -flto -O3 -Wall -I. -I$(HALDIR)
LDFLAGS = -mmcu=$(MCU) -flto -O3
