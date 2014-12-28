
#pragma once

#include <stdint.h>

/**
 * @brief Coroutine context
 */

typedef unsigned cr_context_t;

/**
 * @brief Initialize coroutine
 */

#define cr_init(ctx) do { *(ctx) = 0; } while(0)

/**
 * @brief Begin coroutine
 */

#define cr_begin(ctx) \
	do { \
		switch( *(ctx) ) \
		{ \
		case 0:

/**
 * @brief End coroutine
 */

#define cr_end(ctx) \
		} \
		*(ctx) = 0; \
		return 0; \
	} while(0)

/**
 * @brief Delay coroutine
 */

#define cr_delay(ctx,value) \
	do \
	{ \
		*(ctx) = __LINE__; \
		return (value) ? (value) : 1; \
		case __LINE__:; \
	} while(0)

/**
 * @brief Yield coroutine
 */

#define cr_yield(ctx) cr_delay(ctx,1)

/**
 * @brief Wait until condition becomes true
 */

#define cr_wait_until(ctx,cond) \
	do \
	{ \
		*(ctx) = __LINE__; \
		case __LINE__: \
		if( !(cond) ) return 1; \
	} while(0)

/**
 * @brief Wait while condition is true
 */

#define cr_wait_while(ctx,cond) \
	do \
	{ \
		*(ctx) = __LINE__; \
		case __LINE__: \
		if( cond ) return 1; \
	} while(0)

/**
 * @brief Wait until child coroutine completes
 */
#define cr_wait_coroutine(ctx,coroutine) \
	do \
	{ \
		unsigned delay; \
		*(ctx) = _LINE__; \
		case __LINE__: \
		delay = coroutine; \
		if( delay ) return delay; \
	} while(0)

/**
 * @brief Restart coroutine
 */

#define cr_restart(ctx) \
	do \
	{ \
		*(ctx) = 0; \
		return 1; \
	} while(0)

/**
 * @brief Exit coroutine
 */

#define cr_exit(ctx) \
	do \
	{ \
		*(ctx) = 0; \
		return 0; \
	} while(0)
