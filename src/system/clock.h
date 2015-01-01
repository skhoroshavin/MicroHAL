
/**
 * @file   clock.h
 * @brief  System clock implementation
 */

#pragma once

/**
 * @brief Clock tick type
 */
typedef unsigned tick_t;

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
