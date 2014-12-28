
#include "scheduler.h"
#include <platform/interrupts.h>

struct tasklet_queue_t
{
	struct tasklet_t * head;
	unsigned           delay;
};

struct tasklet_queue_t _tasklets[2] =
{
	{ .head = 0, .delay = -1 },
	{ .head = 0, .delay = -1 }
};
static sched_timer_value_t _last_tick;

void sched_compare_irq()
{

}

static void _sched_process_queue( uint8_t tq, unsigned dt )
{
	struct tasklet_t * tasklet = _tasklets[tq].head;
	_tasklets[tq].head = 0;
	_tasklets[tq].delay = -1;

	while( tasklet )
	{
		struct tasklet_t * next = tasklet->next;

		if( tasklet->delay > dt )
		{
			tasklet->delay -= dt;
			sched_tasklet( tasklet );
		}
		else
			tasklet->func( tasklet->data );

		tasklet = next;
	}
}

void sched_init()
{
	_last_tick = sched_timer_value();
	sched_compare_irq_enable();
	sched_timer_start();
}

void sched_process()
{
	sched_timer_value_t cur_tick, next_tick, dt;
	uint8_t tq;

	cur_tick = sched_timer_value();
	dt = cur_tick - _last_tick;
	dt %= sched_period;
	_last_tick = cur_tick;

	for( tq = 0; tq < 2; ++tq )
		_sched_process_queue( tq, dt );

	if( _tasklets[0].head )
		return;

	if( _tasklets[1].delay < sched_period/2 )
		dt = _tasklets[1].delay;
	else
		dt = sched_period/2;

	next_tick = cur_tick + dt;
	next_tick %= sched_period;
	sched_compare_set_value( next_tick );

	wait_for_irq();
}

void sched_tasklet( struct tasklet_t * tasklet )
{
	uint8_t tq = tasklet->delay > sched_latency ? 1 : 0;

	tasklet->next = _tasklets[tq].head;
	_tasklets[tq].head = tasklet;

	if( tasklet->delay < _tasklets[tq].delay )
		_tasklets[tq].delay = tasklet->delay;
}
