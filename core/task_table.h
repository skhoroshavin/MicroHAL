
#pragma once

#include <stdint.h>

/**
 * @brief Pointer to task function
 *
 * Task function takes pointer to its context and returns number of ticks
 * after which this task should be run again, or 0 if task is terminated
 */
typedef unsigned (*task_t)(void*);

/**
 * @brief Task table entry
 */
struct task_entry_t
{
	task_t   func;
	void *   data;
	unsigned delay;
};

#define BEGIN_TASK_TABLE(name) \
	struct task_entry_t name[] = {

#define END_TASK_TABLE() \
	{ 0, 0, 0 } };

#define TASK_ENTRY(func,data) \
	{ (task_t)(func), (data), 1 },

/**
 * @brief Process task table
 * @param table Task table pointer
 * @param ticks Number of ticks passed from last time this function was called
 * @return Number of ticks after which this function should be run again
 */
unsigned task_table_process( struct task_entry_t * table, unsigned ticks );
