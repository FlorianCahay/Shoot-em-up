#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

#include "../include/linked_list.h"
#include "../include/enemies.h"
#include "../include/shot.h"

/* Top left coordinates and bottom right coordinates */
typedef struct {
	float x;
	float y;
	float x2;
	float y2;
} Rectangle;

/* Each rectangle of a hitbox with size as the number of rectangles */
typedef struct {
	int size;
	Rectangle *rectangle;
} Hitbox;

Hitbox get_hitbox(char *path, int element_width, int element_height);

void shot_hit_enemy(Hitbox hitbox_enemy, Hitbox hitbox_shot_ally, Linked_list *enemies, Linked_list *shots, int* score);

void spaceship_hit_enemy(Hitbox hitbox_spaceship, Hitbox hitbox_enemy, Spaceship spaceship, Linked_list *enemies, int *health);

void spaceship_hit_shot(Hitbox hitbox_spaceship, Hitbox hitbox_shot_enemy, Spaceship spaceship, Linked_list *shots, int *health);

void hitbox_free(Rectangle *rectangle);

#endif