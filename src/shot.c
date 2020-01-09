/*Manage shot structure */ 
#include "../include/shot.h"
#include "../include/linked_list.h"
#include <math.h>
#define SHOT_SIZE 30
#define PI 3.14159265

/*Return a shot with all his properties set */
Shot shot_create(const double x, const double y, double x_move, double y_move, const int speed, const Type type)
{
	Shot shot = {};
	shot.x = x;
	shot.y = y;
	shot.rotation = -((atan((y_move - y) / (x_move - x))) *180 / PI);
	x_move = -(x - x_move); /*Distance from x to x_move */
	y_move = -(y - y_move); /*Distance from y to y_move */
	double total = fabs(x_move) + fabs(y_move); /*Add the two distances */
	shot.x_move = x_move / total * speed; /*Get the x_move for each frame */
	shot.y_move = y_move / total * speed; /*Get the y_move for each frame */
	shot.type = type;
	return shot;
}

/*Move down a shot and return 1 if the shot is out of the screen, return 0 otherwise */
int shot_move(Shot *shot, const int width, const int height)
{
	shot->x += shot->x_move;
	shot->y += shot->y_move;
	if ((shot->x <= -15) || (shot->x >= width) || (shot->y <= 0) || (shot->y >= height))
	{
		return 1;
	}
	return 0;
}

int get_shot_size()
{
	return SHOT_SIZE;
}