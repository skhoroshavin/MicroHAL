
#pragma once

#include <stdint.h>

/***********************************************************************\
 * Set pin to logic 1                                                  *
\***********************************************************************/

#define _gpio_set_pin(PORT,PIN) PORT##_set( 1<<PIN )
#define gpio_set_pin(PORTPIN) _gpio_set_pin(PORTPIN)

/***********************************************************************\
 * Clear pin to logic 0                                                *
\***********************************************************************/

#define _gpio_clear_pin(PORT,PIN) PORT##_clear( 1<<PIN )
#define gpio_clear_pin(PORTPIN) _gpio_clear_pin(PORTPIN)

/***********************************************************************\
 * Read pin logic value                                                *
\***********************************************************************/

#define _gpio_read_pin(PORT,PIN) ((PORT##_read() >> PIN) & 0x1)
#define gpio_read_pin(PORTPIN) _gpio_read_pin(PORTPIN)

/***********************************************************************\
 * Write logic value to pin                                            *
\***********************************************************************/

#define gpio_write_pin(PORTPIN,VALUE) \
	do { \
		if(VALUE) _gpio_set_pin(PORTPIN); \
		else _gpio_clear_pin(PORTPIN); \
	} while(0)

/***********************************************************************\
 * Setup pin                                                           *
\***********************************************************************/

#define _gpio_setup_pin(PORT,PIN,MODE) PORT##_setup(MODE,PIN,1)
#define gpio_setup_pin(PORTPIN,MODE) _gpio_setup_pin(PORTPIN,MODE)
