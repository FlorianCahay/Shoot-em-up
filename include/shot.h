#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "../include/spaceship.h"

typedef struct {
	int x;
	int y;
	int speed;
	int direction;
} Shot;

Shot shot_create(int x, int y, int speed, int direction);
int shot_move(Shot *shot, int window_height);
int get_shot_size();

#endif