#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "../include/star.h"

typedef union{
	Star star;
}Data;

typedef struct ElementL{
	struct ElementL * prev;
	Data data;
	int null;
} Element;

typedef struct{
	Element * last;
} Linked_list;

Linked_list linked_list_create();

void linked_list_append(Linked_list * linked_list,Data data);

void linked_list_pop(Linked_list * linked_list);

void linked_list_remove(Element * elem);

void linked_list_clear(Linked_list * linked_list);

void linked_list_free(Linked_list * linked_list);

#endif