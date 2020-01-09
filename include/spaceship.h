#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

/* Struct defining Spaceship */
typedef struct{
	int x;
	int y;
} Spaceship;

Spaceship spaceship_create(const int x, const int y);

void spaceship_move(int *point, const int value, const int speed);

void spaceship_move_up(Spaceship *spaceship);

void spaceship_move_down(Spaceship *spaceship, const int window_height);

void spaceship_move_left(Spaceship *spaceship);

void spaceship_move_right(Spaceship *spaceship, const int window_width);

void spaceship_show(const Spaceship spaceship);

int get_spaceship_width();

int get_spaceship_height();

int get_spaceship_speed();

#endif