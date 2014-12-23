
/**
 * @file   scheduler.h
 * @brief  Simple task scheduler
 *
 * Task scheduler
 */

#pragma once

#include <core/list.h>

/**
 * @brief Tasklet function
 */
typedef void (*tasklet_func_t)(void*);

/**
 * @brief Tasklet data structure
 */
struct tasklet_t
{
	struct list_t  list;  /**< @brief Linked list containing tasklets (internal) */
	unsigned       delay; /**< @brief Tasklet delay in ticks or periods (internal) */
	tasklet_func_t func;  /**< @brief Pointer to tasklet function */
	void *         data;  /**< @brief Pointer to tasklet data */
};

/**
 * @brief Initialize task scheduler
 */
void sched_init();

/**
 * @brief Process tasklets
 */
void sched_process();

/**
 * @brief Schedule tasklet for immediate execution
 * @param tasklet Tasklet to be executed
 */
void sched_immediate( struct tasklet_t * tasklet );

/**
 * @brief Schedule tasklet for execution in short amount of time
 * @param tasklet Tasklet to be executed
 * @param ticks Number of scheduler ticks
 */
void sched_short( struct tasklet_t * tasklet, unsigned ticks );

/**
 * @brief Schedule tasklet for execution after long amount of time
 * @param tasklet Tasklet to be executed
 * @param periods Number of scheduler periods
 */
void sched_long( struct tasklet_t * tasklet, unsigned periods );
