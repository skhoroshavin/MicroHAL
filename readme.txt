
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
		timer_freq      - timer frequency
		timer_init()    - initialize timer
		timer_value()   - timer current value
		timer_top()     - timer top value
		timer_set_top() - set timer top value

	UART
		uart_init(baud)  - initialize UART
		uart_can_send()  - check if UART is ready to send data
		uart_can_recv()  - check if UART is ready to receive data
		uart_send(value) - send 1 byte
		uart_recv()      - receive 1 byte

Scheduler
=========

	Tick    - time between timer ticks
	Latency - maximum time between timer
	Period  - maximum time between timer interrupts

	Tasklet queues:
		0: Immediate   - 0 wait time
		1: Low-latency - within timer interrupt latency, time stored in timer ticks
		2: Short       - within timer period, time stored in timer ticks
		3: Long        - longer than timer period, time stored in timer periods

	Schedule task:
		if( delay == 0 )
			queue_insert( 0, task )
		else if( delay < latency )
			queue_insert_ordered( 1, task, delay )
		else if( delay < period )
			queue_insert_ordered( 2, task, delay )
		else
			queue_insert_ordered( 3, task, delay/period )

	Update time:
		dt = timer - last_timer
		last_timer += dt
		if( dt )
		{
			for each task in 1
				schedule_task( task, delay )
			for each task in 2
				schedule_task( task, delay )
			for each task in 3
				schedule_task( task, delay*period )
		}

	Idle (tickless):
		if( has_tasklets(2) )
		{
			timer_compare += nearest_time(2)
			wait_for_irq();
		}
		else if( has_tasklets(3) )
		{
			timer_compare += nearest_time(3)
			wait_for_irq();
		}
		else
			deep_sleep();

	Idle (ticked):
		if( has_tasklets(2) || has_tasklets(3) )
			wait_for_irq();
		else
			deep_sleep();

	Schedule:
		while(1)
		{
			update_time()

			while( has_tasklets(0) )
			{
				process_tasklets(0)

				if( !has_tasklets(0) && has_tasklets(1) )
					wait_for_tasklets(1)

				update_time()
			}

			idle();
		}
