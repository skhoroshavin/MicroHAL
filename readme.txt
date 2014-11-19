
Directory structure
===================

	core
		Generic utilities and build scripts
	drivers
		Device drivers, used indirectly through microhal.h by any part of project
	examples
		Working examples


User project
============

	Makefile:
		Define PLATFORM - platform name (AVR,STM32,NORDIC51,etc)
		Define MCU      - controller name
		Define HALDIR   - path to MicroHAL
		Define TARGET   - binary name
		Define SOURCES  - list of used c files
		Include core build.mk
		Define flash target if necessary

	Project must contain microhal.h, because it is included in driver
	implementations

	Driver usage:
		Put driver configuration macros in microhal.h
		Include driver.h in microhal.h after these macros
		Include driver.c in makefile source list


Interfaces
==========

	GPIO
		gpio_init()       - initialize bus
		gpio_write(value) - write value (for output bus)
		gpio_read()       - read value (for input bus)

	Timer
		timer_freq    - timer frequency
		timer_init()  - initialize timer
		timer_value() - timer current value

	UART
		uart_init(baud)  - initialize UART
		uart_can_send()  - check if UART is ready to send data
		uart_can_recv()  - check if UART is ready to receive data
		uart_send(value) - send 1 byte
		uart_recv()      - receive 1 byte


