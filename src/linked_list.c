/*Linked list for keyboard events,shots, stars and spaceships*/ 
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/star.h"
#include "../include/linked_list.h"

/*Initialize a Linked_List */
Linked_list linked_list_create()
{
	Element *last = NULL;
	last = malloc(sizeof(Element));
	if (last == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire linked_list\n");
		exit(EXIT_FAILURE);
	}
	last->null = 1;
	Linked_list linked_list = { last
	};
	return linked_list;
}

/*Append an element on the top of the list */
void linked_list_append(Linked_list *linked_list, Data data)
{
	Element *new_element = NULL;
	new_element = malloc(sizeof(Element));
	if (new_element == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire linked_list_append\n");
		exit(EXIT_FAILURE);
	}
	new_element->prev = linked_list->last;
	new_element->data = data;
	new_element->null = 0;
	linked_list->last = new_element;
}

/*Remove the element on the top of the list */
void linked_list_pop(Linked_list *linked_list)
{
	if (linked_list->last->null == 1)
	{
		return;
	}
	Element *last = linked_list->last;
	linked_list->last = linked_list->last->prev;
	free(last);
	last = NULL;
}

/*Remove the element in parameter in the list */
void linked_list_remove(Element *elem)
{
	Element *elemCopy = elem->prev;
	if (elem->prev->null == 1)
	{
		free(elem->prev);
		elem->null = 1;
		return;
	}
	elem->data = elem->prev->data;
	elem->null = elem->prev->null;
	elem->prev = elem->prev->prev;
	free(elemCopy);
	elemCopy = NULL;
}

/*Remove all elements of the list */
void linked_list_clear(Linked_list *linked_list)
{
	while (linked_list->last->null == 0)
	{
		linked_list_pop(linked_list);
	}
}

/*Free all pointers of the list */
void linked_list_free(Linked_list *linked_list)
{
	linked_list_clear(linked_list);
	free(linked_list->last);
	linked_list->last = NULL;
}