#ifndef STAR_H
#define STAR_H

typedef struct {
	int x;
	int y;
	int size;
	int speed;
} Star;

Star star_create(int x, int y, int size, int speed);

void star_move_down(Star * star);

#endif