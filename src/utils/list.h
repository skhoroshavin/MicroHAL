
#pragma once

#include <core/pp_utils.h>

/**
 * @brief Linked list control structure
 */
struct list_t
{
	struct list_t * prev;
	struct list_t * next;
};
typedef struct list_t list_t;

/**
 * @brief Initialize linked list
 * @param head Head of linked list
 */
void list_init( list_t * head );

/**
 * @brief Get linked list first element
 * @param head Linked list head
 * @return Linked list first element
 */
inline list_t * list_front( list_t * head ) { return head->next; }

/**
 * @brief Get linked list last element
 * @param head Linked list head
 * @return Linked list last element
 */
inline list_t * list_back( list_t * head ) { return head->prev; }

/**
 * @brief Push item to back of the linked list
 * @param head Linked list head
 * @param item Item to be added to list
 */
void list_push_back( list_t * head, list_t * item );

/**
 * @brief Push item to front of the linked list
 * @param head Linked list head
 * @param item Item to be added to list
 */
void list_push_front( list_t * head, list_t * item );

/**
 * @brief Remove item from linked list
 * @param item Item to be removed from list
 */
void list_remove( list_t * item );
