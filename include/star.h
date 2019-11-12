#ifndef STAR_H
#define STAR_H

typedef struct {
	int x;
	int y;
	int size;
	int speed;
} Star;

Star star_create(int x, int y, int size, int speed);

int star_move_down(Star * star,int window_height);

#endif