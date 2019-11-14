#include "../include/shot.h"
#include "../include/linked_list.h"
#include "../include/spaceship.h"

#define SHOT_SIZE 30

/* Return a shot with all his properties set. */
Shot shot_create(int x, int y, int speed) {
	Shot shot = {x, y, speed};
	return shot;
}

/* Move down a shot and return 1 if the shot is out of the screen, if not return 0. */
int shot_move(Shot *shot, int direction, int window_height) {
	if (direction == 0) {
		/* Up */
		shot->y -= shot->speed*1;
		if (shot->y < -SHOT_SIZE) {
			return 1;
		}
	} else if (direction == 1) {
		/* Down */
		shot->y += shot->speed*1;
		if (shot->y > window_height+SHOT_SIZE) {
			return 1;
		}
	}
	return 0;
}

int get_shot_size(){
	return SHOT_SIZE;
}