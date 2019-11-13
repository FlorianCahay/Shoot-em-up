#ifndef STAR_H_INCLUDED
#define STAR_H_INCLUDED

/* Struct defining a star */
typedef struct {
	int x;
	int y;
	int size;
	int speed;
} Star;

Star star_create(int x, int y, int size, int speed);
int star_move_down(Star *tar, int window_height);

#endif