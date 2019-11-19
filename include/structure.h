#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

#include <MLV/MLV_all.h>

typedef struct {
	MLV_Image *star;
	MLV_Image *spaceship;
	MLV_Image *heart;
	MLV_Image *shot_ally;
	MLV_Image *shot_enemy;
	MLV_Image *enemy;
} Images;

typedef struct {
	int x;
	int y;
	int speed;
	int direction;
} Shot;

/* Struct defining Spaceship */
typedef struct{
	int x;
	int y;
} Spaceship;



#endif