
Directory structure
===================

	src          - Main source tree
		platform - Platform dependent functions and build scripts
		utils    - Generic utilities
		drivers  - Device drivers, used indirectly through hal.h by any part of project
		system   - Operating system, depends on platform, utils and hal.h
	demo         - Demo project
		arduino  - Arduino HAL for demo project

User project
============

	Makefile:
		Define PLATFORM - platform name (AVR,STM32,NORDIC51,etc)
		Define MCU      - controller name
		Define OSDIR    - path to MicroOS
		Define TARGET   - binary name
		Define SOURCES  - list of used c files
		Include core build.mk
		Define flash target if necessary

	Project must contain hal.h, because it is included in driver
	implementations

	Driver usage:
		Put driver configuration macros in hal.h
		Include driver.h in hal.h after these macros
		Include driver.c in makefile source list


Interfaces
==========

	GPIO
		gpio_init()       - initialize bus
		gpio_write(value) - write value (for output bus)
		gpio_read()       - read value (for input bus)

	Timer
		timer_freq             - timer frequency
		timer_init()           - initialize timer
		timer_start()          - start timer
		timer_stop()           - stop timer
		timer_value()          - timer current value
		timer_set_value(value) - set timer current value

	Timer compare
		compare_value()
		compare_set_value()
		compare_irq_enable()
		compare_irq_disable()
		compare_irq()

	UART
		uart_init(baud)  - initialize UART
		uart_can_send()  - check if UART is ready to send data
		uart_can_recv()  - check if UART is ready to receive data
		uart_send(value) - send 1 byte
		uart_recv()      - receive 1 byte
