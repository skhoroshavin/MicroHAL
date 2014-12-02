
#pragma once

#include <stdint.h>
#include <core/list.h>

/**
 * @brief Pointer to task function
 *
 * Task function takes pointer to its context and returns number of ticks
 * after which this task should be run again, or 0 if task is terminated
 */
typedef unsigned (*task_t)(void*);

/**
 * @brief Task item
 */
struct task_item_t
{
	list_t    timer_queue; /**< @brief Timer queue pointer */
	unsigned  delay;       /**< @brief Delay in ticks after which task should be started */
	task_t    task;        /**< @brief Pointer to task function */
	void *    context;     /**< @brief Pointer to task context */
};
typedef struct task_item_t task_item_t;

#define DEFINE_TASK(name,handler,context_type) \
	context_type name##_context; \
	task_item_t name = { \
		.delay = 1, \
		.task  = (task_t)handler, \
		.context = &name##_context \
	};

/**
 * @brief Task queue
 */
struct task_queue_t
{
	list_t timer_queue; /**< Timer queue header */

};
typedef struct task_queue_t task_queue_t;

/**
 * @brief Initialize task queue
 * @param tq Task queue pointer
 */
void task_queue_init( task_queue_t * tq );

/**
 * @brief Add delayed task to queue
 * @param tq Task queue pointer
 * @param item Task item pointer
 * @param delay Delay in ticks after which task should be started
 */
void task_queue_add_delayed( task_queue_t * tq, task_item_t * item, unsigned delay );

/**
 * @brief Add task to queue
 * @param tq Task queue pointer
 * @param item Task item pointer
 */
inline void task_queue_add( task_queue_t * tq, task_item_t * item ) { task_queue_add_delayed( tq, item, 1 ); }

/**
 * @brief Process task queue
 * @param tq Task queue pointer
 * @param ticks Number of ticks passed from last time this function was called
 * @return Number of ticks after which this function should be run again
 */
unsigned task_queue_process( task_queue_t * tq, unsigned ticks );

