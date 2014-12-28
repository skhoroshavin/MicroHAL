
#include <utils/list.h>

void list_init( list_t * head )
{
	head->prev = head;
	head->next = head;
}

inline void __list_insert( list_t * prev, list_t * next, list_t * value )
{
	prev->next = value;
	value->prev = prev;
	value->next = next;
	next->prev = value;
}

void list_push_back( list_t * head, list_t * item )
{
	__list_insert( head->prev, head, item );
}

void list_push_front( list_t * head, list_t * item )
{
	__list_insert( head, head->next, item );
}

void list_remove( list_t * item )
{
	item->prev->next = item->next;
	item->next->prev = item->prev;
}
