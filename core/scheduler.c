
#include "scheduler.h"
#include "microhal.h"
#include <core/interrupts.h>

static struct tasklet_t * _tasklets_immediate = 0;
static struct tasklet_t * _tasklets_near      = 0;
static struct tasklet_t * _tasklets_short     = 0;
static struct tasklet_t * _tasklets_long      = 0;

static inline void add_tasklet( struct tasklet_t ** head, struct tasklet_t * tasklet )
{
	tasklet->next = *head;
	*head = tasklet;
}

void sched_init()
{
	sched_timer_init();
}

void sched_process()
{

}

void sched_immediate( struct tasklet_t * tasklet )
{
	irq_state_t irq_state = irq_store_and_disable();
	add_tasklet( &_tasklets_immediate, tasklet );
	irq_restore( irq_state );
}

void sched_short( struct tasklet_t * tasklet, unsigned ticks )
{
	irq_state_t irq_state = irq_store_and_disable();
	tasklet->delay = ticks;
	if( ticks <= sched_latency ) add_tasklet( &_tasklets_near, tasklet );
	else add_tasklet( &_tasklets_short, tasklet );
	irq_restore( irq_state );
}

void sched_long( struct tasklet_t * tasklet, unsigned periods )
{
	irq_state_t irq_state = irq_store_and_disable();
	tasklet->delay = periods;
	add_tasklet( &_tasklets_long, tasklet );
	irq_restore( irq_state );
}
