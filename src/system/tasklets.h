
/**
 * @file   tasklets.h
 * @brief  Tasklets scheduler
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
void tasklets_init();

/**
 * @brief Process tasklets
 */
void tasklets_process();

/**
 * @brief Schedule tasklet for execution
 * @param tq Tasklet queue ID (0 - immediate, 1 - delayed execution)
 * @param tasklet Tasklet to be executed
 */
void tasklets_add( struct tasklet_t * tasklet );

/**
 * @brief Schedule tasklet for delayed execution
 * @param tasklet Tasklet to be executed
 * @param ticks Execution delay in ticks
 */
inline void tasklets_delay( struct tasklet_t * tasklet, unsigned ticks ) { tasklet->delay = ticks; tasklets_add( tasklet ); }
