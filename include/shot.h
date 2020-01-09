#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "../include/spaceship.h"

/* Shot type*/
typedef enum {ALLY, ENEMY} Type;

typedef struct {
	double x; 			/* x coordinate*/
	double y; 			/* y coordinate */
	double x_move; 		/* x_move for each frame */
	double y_move; 		/* y_move for each frame */
	double rotation; 	/* Shot rotation to apply */
	Type type; 			/* Shot type */
}Shot;

Shot shot_create(const double x, const double y, double x_move, double y_move, const int speed, const Type type);
int shot_move(Shot *shot, const int width, const int height);
int get_shot_size();

#endif