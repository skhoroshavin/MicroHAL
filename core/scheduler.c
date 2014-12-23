
#include "scheduler.h"
#include "microhal.h"

static struct list_t _tasklets_immediate;
static struct list_t _tasklets_near;
static struct list_t _tasklets_short;
static struct list_t _tasklets_long;

void sched_init()
{
	list_init( &_tasklets_immediate );
	list_init( &_tasklets_near );
	list_init( &_tasklets_short );
	list_init( &_tasklets_long );

	sched_timer_init();
}

void sched_process()
{

}

void sched_immediate( struct tasklet_t * tasklet )
{
	list_push_front( &_tasklets_immediate, &tasklet->list );
}

void sched_short( struct tasklet_t * tasklet, unsigned delay )
{

}

void sched_long( struct tasklet_t * tasklet, unsigned delay )
{

}
