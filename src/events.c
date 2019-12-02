/* Manage keyboard events list */
#include "../include/events.h"

/* Return 1 if the events list contains the event, 0 otherwise */
int events_contains(Linked_list * events,MLV_Keyboard_button key){
	Element * last = events->last;
	while(last->null==0){ /* Loop over events */
		if(last->data.key==key){
			return 1;
		}
		last=last->prev;
	}
	return 0;
}

/* Add event to events list if the event is not already the list */
void events_add_event(Linked_list * events,MLV_Keyboard_button key){
	if(!events_contains(events,key)){
		Data data;
		data.key=key; /* Initialize union */
		linked_list_append(events,data);
	}
}

/* Remove event from the list */
void events_remove_event(Linked_list * events,MLV_Keyboard_button key){
	Element * last = events->last;
	while(last->null==0){ /* Loop over events */
		if(last->data.key==key){ 
			linked_list_remove(last);
			break;
		}
		if(last->null==0){
			last=last->prev;
		}
	}
}