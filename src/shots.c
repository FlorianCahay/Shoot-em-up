#include "../include/shots.h"

/* Move all shots. */
void shots_move(Linked_list *shots, int window_height) {
	Element *last = shots->last;
	while (last->null == 0) {
		if (shot_move(&last->data.shot, window_height)){
			linked_list_remove(last);
		}
		last = last->prev;
	}
}

/* Add a shot to the shots. */
void shots_create_shot(Linked_list *shots, Spaceship spaceship, int spaceship_width, int spaceship_height, int direction) {
	Data data;
	Data data_2;
	if (direction == 0) {
		Shot shot = shot_create(spaceship.x+5, spaceship.y, 2, direction);
		data.shot = shot;
		Shot shot_2 = shot_create(spaceship.x+(spaceship_width-8), spaceship.y, 2, direction);
		data_2.shot = shot_2;
		linked_list_append(shots, data);
		linked_list_append(shots, data_2);	
	} else if (direction == 1) {
		Shot shot = shot_create(spaceship.x+(spaceship_width/2), spaceship.y+(spaceship_height/2), 2, direction);
		data.shot = shot;
		linked_list_append(shots, data);
	}
}