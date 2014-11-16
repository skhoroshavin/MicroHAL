
CC = avr-gcc

CCFLAGS = -mmcu=$(MCU) -flto -O3 -Wall -I$(HALDIR)
LDFLAGS = -mmcu=$(MCU) -flto -O3
