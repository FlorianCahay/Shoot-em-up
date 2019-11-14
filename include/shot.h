#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "../include/spaceship.h"

typedef struct {
	int x;
	int y;
	int speed;
} Shot;

Shot shot_create(int x, int y, int speed);
int shot_move(Shot *shot, int direction, int window_height);/*
void shots_create_shot(Linked_list *shots, Spaceship spaceship);*/

#endif