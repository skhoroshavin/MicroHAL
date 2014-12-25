
/**
 * @file   scheduler.h
 * @brief  Simple task scheduler
 *
 * Task scheduler requirements:
 *
 */

#pragma once

#include "hal.h"

/**
 * @brief Tasklet function
 */
typedef void (*tasklet_func_t)(void*);

/**
 * @brief Tasklet data structure
 */
struct tasklet_t
{
	struct tasklet_t * next;  /**< @brief Pointer to next tasklet in list (internal) */
	unsigned           delay; /**< @brief Tasklet delay in ticks or periods (internal) */
	tasklet_func_t     func;  /**< @brief Pointer to tasklet function */
	void *             data;  /**< @brief Pointer to tasklet data */
};

/**
 * @brief Tasklet data initializer
 */
#define DEFINE_TASKLET(NAME,FUNC,DATA) \
	struct tasklet_t NAME = \
	{ \
		.next  = 0, \
		.delay = 0, \
		.func  = (tasklet_func_t)(FUNC), \
		.data  = (void*)(DATA) \
	}

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
