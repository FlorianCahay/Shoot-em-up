#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#include "../include/star.h"

/* Different types. */
typedef union{
	Star star;
} Data;

/* Struct of a list element. */
typedef struct ElementL{
	struct ElementL *prev;
	Data data;
	int null; /* null : 1, notnull :0 */
} Element;

/* List struct with the top element. */
typedef struct{
	Element *last;
} Linked_list;

Linked_list linked_list_create();

void linked_list_append(Linked_list *linked_list, Data data);

void linked_list_pop(Linked_list *linked_list);

void linked_list_remove(Element *elem);

void linked_list_clear(Linked_list *linked_list);

void linked_list_free(Linked_list *linked_list);

#endif