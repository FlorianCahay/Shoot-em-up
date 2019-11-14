#include "../include/shot.h"
#include "../include/linked_list.h"
#include "../include/spaceship.h"

void shots_move(Linked_list *shots, int window_height);;
void shots_create_shot(Linked_list *shots, Spaceship spaceship, int spaceship_width);

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
		if (shot->y < -30) {
			return 1;
		}
	} else if (direction == 1) {
		/* Down */
		shot->y += shot->speed*1;
		if (shot->y > window_height+30) {
			return 1;
		}
	}
	return 0;
}

/* Move all shots. */
void shots_move(Linked_list *shots, int window_height) {
	Element *last = shots->last;
	while (last->null == 0) {
		if (shot_move(&last->data.shot, 0, window_height)){
			linked_list_remove(last);
		}
		last = last->prev;
	}
}

/* Add a shot to the shots. */
void shots_create_shot(Linked_list *shots, Spaceship spaceship, int spaceship_width) {
	Shot shot = shot_create(spaceship.x+5, spaceship.y, 2);
	Data data;
	data.shot = shot;
	Shot shot_2 = shot_create(spaceship.x+(spaceship_width-8), spaceship.y, 2);
	Data data_2;
	data_2.shot = shot_2;

	linked_list_append(shots, data);
	linked_list_append(shots, data_2);
}