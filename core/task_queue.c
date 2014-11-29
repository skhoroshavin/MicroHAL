
#include "task_queue.h"

void task_queue_init( task_queue_t * tq )
{
	list_init( &tq->timer_queue );
}

void task_queue_add_delayed( task_queue_t * tq, task_item_t * item, unsigned delay )
{
	item->delay = delay;
	list_push_front( &tq->timer_queue, &item->timer_queue );
}

unsigned task_queue_process( task_queue_t * tq, unsigned ticks )
{
	unsigned min_delay = -1;
	list_t * pos;

	for( pos = tq->timer_queue.next;
		 pos != &tq->timer_queue;
		 pos = pos->next )
	{
		task_item_t * task = list_item( pos, task_item_t, timer_queue );

		if( task->delay > ticks ) task->delay -= ticks;
		else task->delay = task->task( task->context );

		if( !task->delay )
			list_remove( pos );

		if( task->delay < min_delay ) min_delay = task->delay;
	}

	return min_delay;
}
