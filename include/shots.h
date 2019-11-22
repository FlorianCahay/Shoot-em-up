#ifndef SHOTS_H_INCLUDED
#define SHOTS_H_INCLUDED

#include "../include/spaceship.h"
#include "../include/linked_list.h"

void shots_move(Linked_list *shots, int window_width, int window_height);
void shots_create_shot(Linked_list *shots, Spaceship spaceship, int spaceship_width, int spaceship_height,Spaceship player, int window_height, Type type);

#endif