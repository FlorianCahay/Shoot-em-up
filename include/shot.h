#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "../include/spaceship.h"

typedef enum {ALLY, ENEMY} Type;

typedef struct {
	double x;
	double y;
	double x_move;
	double y_move;
	double rotation;
	Type type;
}Shot;

Shot shot_create(int x, int y, double x_move, double y_move, int speed, Type type);
int shot_move(Shot *shot, int width, int height);
int get_shot_size();

#endif