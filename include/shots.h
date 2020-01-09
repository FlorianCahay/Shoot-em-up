#ifndef SHOTS_H_INCLUDED
#define SHOTS_H_INCLUDED

#include "../include/spaceship.h"
#include "../include/linked_list.h"

void shots_move(Linked_list *shots, const int window_width, const int window_height);
void shots_create_shot(Linked_list *shots, const Spaceship spaceship, const int spaceship_width, const int spaceship_height, const Spaceship player, const Type type);

#endif