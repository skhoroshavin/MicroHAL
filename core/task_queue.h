
#pragma once

#include <core/linked_list.h>

/**
 * @brief Pointer to task function
 *
 * Task function takes pointer to its context and returns number of ticks
 * after which this task should be run again, or 0 if task is terminated
 */
typedef unsigned (*task_t)(void*);

typedef struct
{
	linked_list_t queue;
	unsigned      delay;
	task_t        task;
	void *        context;
} tasklet_t;

typedef struct
{

} task_queue_t;

/**
 * @brief Initialize task queue
 * @param tq Task queue pointer
 */
void task_queue_init( task_queue_t * tq );

/**
 * @brief Process task queue
 * @param tq Task queue pointer
 * @param ticks Number of ticks passed from last time this function was called
 * @return Number of ticks after which this function should be run again
 */
unsigned task_queue_process( task_queue_t * tq, unsigned ticks );

/**
 * @brief Add task to queue
 * @param tq Task queue pointer
 * @param task
 * @param context
 * @param delay
 */
void task_queue_add( task_queue_t * tq, task_t task, void * context, unsigned delay );

