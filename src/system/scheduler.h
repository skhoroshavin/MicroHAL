
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
 * @brief Tasklet queue index identifiers
 */
enum tasklet_queue_index_t
{
	TASKLET_QUEUE_NOW,   /**< Execution within sched_latency time */
	TASKLET_QUEUE_SHORT, /**< Execution within sched_period time */
	TASKLET_QUEUE_LONG,  /**< Execution after sched_period time */

	TASKLET_QUEUE_COUNT
};

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
 * @brief Schedule tasklet
 * @param tasklet Tasklet to be executed
 * @param tq Tasklet queue identifier
 * @param delay Execution delay
 */
void sched_tasklet( struct tasklet_t * tasklet, enum tasklet_queue_index_t tq, unsigned delay );

/**
 * @brief Schedule tasklet for immediate execution
 * @param tasklet Tasklet to be executed
 */
inline void sched_now( struct tasklet_t * tasklet )
{
	sched_tasklet( tasklet, TASKLET_QUEUE_NOW, 0 );
}

/**
 * @brief Schedule tasklet for delayed execution
 * @param tasklet Tasklet to be executed
 * @param ms Execution delay in milliseconds
 */
void sched_delay_ms( struct tasklet_t * tasklet, unsigned ms );
