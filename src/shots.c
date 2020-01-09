/*Manage shots list */ 
#include "../include/shots.h"

/*Move all shots */
void shots_move(Linked_list *shots, const int window_width, const int window_height)
{
	Element *shot = shots->last;
	while (shot->null == 0)
	{
		if (shot_move(&shot->data.shot, window_width, window_height))
		{
			linked_list_remove(shot);
		}
		if (shot->null == 0)
		{
			shot = shot->prev;
		}
	}
}

/*Add a shot to the shots */
void shots_create_shot(Linked_list *shots, const Spaceship spaceship, const int spaceship_width, const int spaceship_height, const Spaceship player, const Type type)
{
	Data data;
	if (type == ALLY)
	{ /*Ally shot */
		Shot shot = shot_create(spaceship.x - 10, spaceship.y, spaceship.x - 10, 0, 2, type);
		data.shot = shot;
		linked_list_append(shots, data);
		Shot shot2 = shot_create(spaceship.x + (spaceship_width - 8) - 15, spaceship.y, spaceship.x + (spaceship_width - 8) - 15, 0, 2, type);
		data.shot = shot2;
		linked_list_append(shots, data);
	}
	else
	{ /*Enemy shot */
		Shot shot = shot_create(spaceship.x + (spaceship_width / 2) - 15, spaceship.y + (spaceship_height / 2), player.x + (get_spaceship_width() / 2) - 15, player.y + (get_spaceship_height() / 2), 2, type);
		data.shot = shot;
		linked_list_append(shots, data);
	}
}