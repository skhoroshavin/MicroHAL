
#pragma once

#include <stdint.h>

/***********************************************************************\
 * Define task context                                                 *
\***********************************************************************/

#define BEGIN_CONTEXT(name) \
	typedef struct \
	{ \
		unsigned __state;

#define END_CONTEXT(name) \
	} name;

/***********************************************************************\
 * Initialize task                                                     *
\***********************************************************************/

#define task_init(ctx) do { (ctx)->__state = 0; } while(0)

/***********************************************************************\
 * Begin task                                                          *
\***********************************************************************/

#define task_begin(ctx) \
	do { \
		switch( (ctx)->__state ) \
		{ \
		case 0:

/***********************************************************************\
 * End task                                                            *
\***********************************************************************/

#define task_end(ctx) \
		} \
		(ctx)->__state = 0; \
		return 0; \
	} while(0)

/***********************************************************************\
 * Delay task                                                          *
\***********************************************************************/

#define task_delay(ctx,value) \
	do \
	{ \
		(ctx)->__state = __LINE__; \
		return (value) ? (value) : 1; \
		case __LINE__:; \
	} while(0)

/***********************************************************************\
 * Yield task                                                          *
\***********************************************************************/

#define task_yield(ctx) task_delay(ctx,1)

/***********************************************************************\
 * Wait until condition                                                *
\***********************************************************************/

#define task_wait_until(ctx,cond) \
	do \
	{ \
		(ctx)->__state = __LINE__; \
		case __LINE__: \
		if( !(cond) ) return 1; \
	} while(0)

/***********************************************************************\
 * Wait while                                                          *
\***********************************************************************/

#define task_wait_while(ctx,cond) \
	do \
	{ \
		(ctx)->__state = __LINE__; \
		case __LINE__: \
		if( cond ) return 1; \
	} while(0)

/***********************************************************************\
 * Task restart                                                        *
\***********************************************************************/

#define task_restart(ctx) \
	do \
	{ \
		(ctx)->__state = 0; \
		return 1; \
	} while(0)

/***********************************************************************\
 * Task exit                                                           *
\***********************************************************************/

#define task_exit(ctx) \
	do \
	{ \
		(ctx)->__state = 0; \
		return 0; \
	} while(0)
