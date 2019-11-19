#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

typedef struct {
	float x;
	float y;
	float x2;
	float y2;
} Rectangle;

typedef struct {
	int size;
	Rectangle *rectangle;
} Hitbox;

Hitbox get_hitbox(char *path);

#endif