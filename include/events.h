#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include <MLV/MLV_all.h>
#include "../include/linked_list.h"

int events_contains(Linked_list * events, const MLV_Keyboard_button key);

void events_add_event(Linked_list * events, const MLV_Keyboard_button key);

void events_remove_event(Linked_list * events, const MLV_Keyboard_button key);

#endif