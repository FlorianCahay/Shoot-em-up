#include <stdio.h>
#include "../include/spaceship.h"

#define SPACESHIP_WIDTH 50
#define SPACESHIP_HEIGHT 50
#define SPACESHIP_SPEED 5

/* Create a spaceship with x and y coordinates. */
Spaceship spaceship_create(int x, int y){
	Spaceship spaceship = {};
	spaceship.x = x;
	spaceship.y = y;
	return spaceship; 
}

/* Add value to a point of the spaceship. */
void spaceship_move(int *point, int value, int speed){
	*point = *point + value * speed;
}

/* Move the spaceship to the up. */
void spaceship_move_up(Spaceship *spaceship){
	if (spaceship->y-1 < 0) {
		return;
	}
	spaceship_move(&spaceship->y, -1, SPACESHIP_SPEED);
}

/* Move the spaceship to the down. */
void spaceship_move_down(Spaceship *spaceship, int window_height){
	if(spaceship->y+1 > window_height-get_spaceship_height()){
		return;
	}
	spaceship_move(&spaceship->y, +1, SPACESHIP_SPEED);
}

/* Move the spaceship to the left. */
void spaceship_move_left(Spaceship *spaceship){
	if(spaceship->x-1 < 0){
		return;
	}
	spaceship_move(&spaceship->x, -1, SPACESHIP_SPEED);
}

/* Move the spaceship to the right. */
void spaceship_move_right(Spaceship *spaceship, int window_width){
	if(spaceship->x+1 > window_width-get_spaceship_width()){
		return;
	}
	spaceship_move(&spaceship->x, +1, SPACESHIP_SPEED);
}

/* Show coordinates of the spaceship. */
void spaceship_show(Spaceship spaceship){
	printf("spaceship x:%d y:%d\n", spaceship.x, spaceship.y);
}

/* Return constant SPACESHIP_WIDTH. */
int get_spaceship_width() {
	return SPACESHIP_WIDTH;
}

/* Return constant SPACESHIP_HEIGHT. */
int get_spaceship_height() {
	return SPACESHIP_HEIGHT;
}

/* Return constant SPACESHIP_SPEED. */
int get_spaceship_speed() {
	return SPACESHIP_SPEED;
}