
Directory structure
===================

	core
		Platform independent macros and functions
	ports
		Platform dependent low-level drivers, used indirectly through
		microhal.h by any part of project
	drivers
		Platform independent drivers, used indirectly through microhal.h
		by any part of project
	examples
		Working examples


User project
============

	Makefile:
		Define HALDIR - path to MicroHAL
		Define TARGET - binary name
		Define SOURCES - list of used c files
		Define MCU - platform specific controller name
		Include platform-specific build.mk
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


