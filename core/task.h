
#pragma once

#include <stdint.h>

/**
 * @brief Task context
 */

typedef unsigned task_context_t;

/**
 * @brief Initialize task
 */

#define task_init(ctx) do { *(ctx) = 0; } while(0)

/**
 * @brief Begin task
 */

#define task_begin(ctx) \
	do { \
		switch( *(ctx) ) \
		{ \
		case 0:

/**
 * @brief End task
 */

#define task_end(ctx) \
		} \
		*(ctx) = 0; \
		return 0; \
	} while(0)

/**
 * @brief Delay task
 */

#define task_delay(ctx,value) \
	do \
	{ \
		*(ctx) = __LINE__; \
		return (value) ? (value) : 1; \
		case __LINE__:; \
	} while(0)

/**
 * @brief Yield task
 */

#define task_yield(ctx) task_delay(ctx,1)

/**
 * @brief Wait until condition becomes true
 */

#define task_wait_until(ctx,cond) \
	do \
	{ \
		*(ctx) = __LINE__; \
		case __LINE__: \
		if( !(cond) ) return 1; \
	} while(0)

/**
 * @brief Wait while condition is true
 */

#define task_wait_while(ctx,cond) \
	do \
	{ \
		*(ctx) = __LINE__; \
		case __LINE__: \
		if( cond ) return 1; \
	} while(0)

/**
 * @brief Wait until child task completes
 */
#define task_wait_task(ctx,task) \
	do \
	{ \
		unsigned delay; \
		*(ctx) = _LINE__; \
		case __LINE__: \
		delay = task; \
		if( delay ) return delay; \
	} while(0)

/**
 * @brief Restart task
 */

#define task_restart(ctx) \
	do \
	{ \
		*(ctx) = 0; \
		return 1; \
	} while(0)

/**
 * @brief Exit task
 */

#define task_exit(ctx) \
	do \
	{ \
		*(ctx) = 0; \
		return 0; \
	} while(0)
