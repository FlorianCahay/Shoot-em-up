#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <MLV/MLV_all.h>

/* Infos for an animation */
typedef struct {
	int current_frame;
	int total_frame;
	int position_x;
	int position_y;
	MLV_Animation_player *player;
} Animation;


#endif