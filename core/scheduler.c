
#include "scheduler.h"
#include "microhal.h"
#include <core/interrupts.h>

static struct tasklet_t * _tasklets_immediate = 0;
static struct tasklet_t * _tasklets_near      = 0;
static struct tasklet_t * _tasklets_short     = 0;
static struct tasklet_t * _tasklets_long      = 0;

static sched_timer_value_t _last_tick;

#define _sched_add(head,tasklet) \
	do { \
		(tasklet)->next = (head); \
		(head) = (tasklet); \
	} while(0)

#define _sched_add_atomic(head,tasklet) \
	do { \
		irq_state_t irq_state = irq_store_and_disable(); \
		_sched_add(head,tasklet); \
		irq_restore( irq_state ); \
	} while(0)

#define SCHED_FOREACH_TASKLET_BEGIN(head) \
	{ \
		irq_disable(); \
		struct tasklet_t * tasklet = head; \
		head = 0; \
		irq_enable(); \
		while( tasklet ) \
		{ \
			struct tasklet_t * next = tasklet->next;

#define SCHED_FOREACH_TASKLET_END() \
			tasklet = next; \
		} \
	}

static inline void _sched_process_immediate()
{
	SCHED_FOREACH_TASKLET_BEGIN(_tasklets_immediate)
		tasklet->func( tasklet->data );
	SCHED_FOREACH_TASKLET_END()
}

static inline void _sched_process_near( sched_timer_value_t dt )
{
	SCHED_FOREACH_TASKLET_BEGIN(_tasklets_near)
		if( tasklet->delay > dt )
		{
			tasklet->delay -= dt;
			_sched_add( _tasklets_near, tasklet );
		}
		else
			tasklet->func( tasklet->data );
	SCHED_FOREACH_TASKLET_END()
}

static inline void _sched_process_short( sched_timer_value_t dt )
{
	SCHED_FOREACH_TASKLET_BEGIN(_tasklets_short)
		if( tasklet->delay > dt )
		{
			tasklet->delay -= dt;
			if( tasklet->delay > sched_latency )
				_sched_add( _tasklets_short, tasklet );
			else
				_sched_add( _tasklets_near, tasklet );
		}
		else
			tasklet->func( tasklet->data );
	SCHED_FOREACH_TASKLET_END()
}

static inline void _sched_process_long( sched_timer_value_t dt )
{

}

void sched_init()
{
	sched_timer_init();
	_last_tick = sched_timer_value();
}

void sched_process()
{
	while( _tasklets_immediate || _tasklets_near )
	{
		_sched_process_immediate();

		sched_timer_value_t tick = sched_timer_value();
		if( tick == _last_tick ) continue;

		sched_timer_value_t dt = tick - _last_tick;
		dt %= sched_period;
		_last_tick = tick;

		_sched_process_near( dt );
		_sched_process_short( dt );
		_sched_process_long( dt );
	}
}

void sched_immediate( struct tasklet_t * tasklet )
{
	_sched_add_atomic( _tasklets_immediate, tasklet );
}

void sched_short( struct tasklet_t * tasklet, unsigned ticks )
{
	tasklet->delay = ticks;
	_sched_add_atomic( _tasklets_short, tasklet );
}

void sched_long( struct tasklet_t * tasklet, unsigned periods )
{
	tasklet->delay = periods;
	_sched_add_atomic( _tasklets_long, tasklet );
}
