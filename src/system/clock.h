
/**
 * @file   clock.h
 * @brief  System clock implementation
 */

#pragma once

#include "hal.h"

/**
 * @brief Clock tick type
 */
typedef clock_timer_t tick_t;

/**
 * @brief Convert milliseconds to ticks
 */
#define ms2ticks(ms) ((unsigned long long)clock_timer_freq*(ms)/1000)

/**
 * @brief Convert microseconds to ticks
 */
#define us2ticks(us) ((unsigned long long)clock_timer_freq*(us)/1000000)

/**
 * @brief Clock timeout handler (user-defined function)
 * @param dt Ticks since last call
 * @return Ticks until next timeout or 0 if not needed
 */
tick_t clock_timeout( tick_t ticks );

/**
 * @brief Initialize system clock
 */
void clock_init();

/**
 * @brief Current system clock value
 * @return Current system clock value
 */
tick_t clock_value();

/**
 * @brief Set system clock timeout
 * @param ticks Number of ticks after which timeout callback should be called
 */
void clock_set_timeout( tick_t timeout );

/**
 * @brief Clock software IRQ
 */
void clock_soft_irq();
