
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

struct task_item_t
{
	list_t    timer_queue;
	unsigned  delay;
	task_t    task;
	void *    context;
};
typedef struct task_item_t task_item_t;

#define DEFINE_TASK(name,handler,context_type) \
	context_type name##_context; \
	task_item_t name = { \
		.delay = 1, \
		.task  = (task_t)handler, \
		.context = &name##_context \
	};




struct task_queue_t
{
	list_t timer_queue;

};
typedef struct task_queue_t task_queue_t;

/**
 * @brief Initialize task queue
 * @param tq Task queue pointer
 */
void task_queue_init( task_queue_t * tq );

void task_queue_add_delayed( task_queue_t * tq, task_item_t * item, unsigned delay );

inline void task_queue_add( task_queue_t * tq, task_item_t * item ) { task_queue_add_delayed( tq, item, 1 ); }

/**
 * @brief Process task queue
 * @param tq Task queue pointer
 * @param ticks Number of ticks passed from last time this function was called
 * @return Number of ticks after which this function should be run again
 */
unsigned task_queue_process( task_queue_t * tq, unsigned ticks );

