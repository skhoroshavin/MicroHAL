
Directory structure
===================

	core
		Platform independent macros and functions, can be directly used
		by any part of project
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
		Define platform specific macros (CPU, F_CPU, etc)
		Include platform-specific build.mk
		Include core build.mk
		Define flash target if necessary

	Project must contain microhal.h, because it is included in driver implementations

	Driver usage:
		Put driver configuration macros in microhal.h
		Include driver.h in microhal.h after these macros
		Include driver.c in makefile source list


Interfaces
==========

	GPIO

	Timer

	UART
