#include "../include/shot.h"
#include "../include/linked_list.h"
#include "../include/spaceship.h"
#include <math.h>

#define SHOT_SIZE 30
#define PI 3.14159265

/* Return a shot with all his properties set. */
Shot shot_create(int x, int y, double x_move, double y_move,int speed,Type type){
	Shot shot = {};
	shot.x=x;
	shot.y=y;
	shot.rotation=-((atan((y_move-y)/(x_move-x)))*180/PI);
	x_move=-(x-x_move);
	y_move=-(y-y_move);
	double total=fabs(x_move)+fabs(y_move);
	x_move=x_move/total*speed;
	y_move=y_move/total*speed;;
	shot.x_move=x_move;
	shot.y_move=y_move;
	shot.type=type;
	return shot;
}

/* Move down a shot and return 1 if the shot is out of the screen, if not return 0. */
int shot_move(Shot * shot,int width,int height){
	shot->x+=shot->x_move;
	shot->y+=shot->y_move;
	if(shot->x <= -15 || shot->x >= width || shot->y <= 0 || shot->y >= height){
		return 1;
	}
	return 0;
}

int get_shot_size(){
	return SHOT_SIZE;
}