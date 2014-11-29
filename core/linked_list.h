
#pragma once

/**
 * @brief Linked list control structure
 */
struct linked_list_t
{
	struct linked_list_t * prev;
	struct linked_list_t * next;
};
typedef struct linked_list_t linked_list_t;

