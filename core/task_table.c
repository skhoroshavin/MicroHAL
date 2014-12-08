
#include "task_table.h"

unsigned task_table_process( struct task_entry_t * table, unsigned ticks )
{
	unsigned min_delay = -1;

	for( ; table->func; ++table )
	{
		if( !table->delay ) continue;

		if( table->delay > ticks )
			table->delay -= ticks;
		else
			table->delay = table->func( table->data );

		if( table->delay && (table->delay < min_delay) )
			min_delay = table->delay;
	}

	return min_delay;
}
