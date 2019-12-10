/*Manage stars list */ 
#include <MLV/MLV_all.h>
#include "../include/linked_list.h"

/*Print informations of each star */
void stars_show(Linked_list stars)
{
	Element *star = stars.last;
	while (star->null == 0)
	{ /*Loop over stars */
		printf("star x:%d y:%d size:%d speed:%d\n", star->data.star.x, star->data.star.y, star->data.star.size, star->data.star.speed);
		star = star->prev;
	}
}

/*Move all stars down */
void stars_move_down(Linked_list *stars, int window_height)
{
	Element *star = stars->last;
	while (star->null == 0)
	{ /*Loop over stars */
		if (star_move_down(&star->data.star, window_height))
		{ /*If star out of screen */
			linked_list_remove(star);
		}
		if (star->null == 0)
		{
			star = star->prev;
		}
	}
}

/*Add a star to the stars if rand%4==0 */
void stars_create_star(Linked_list *stars, int window_width)
{
	if (rand() % 4 == 0)
	{
		int random_x = MLV_get_random_integer(-30, window_width);
		int random_speed = MLV_get_random_integer(1, 5);
		int random_size = MLV_get_random_integer(20, 30);
		Star star = star_create(random_x, -30, random_size, random_speed);
		Data data;
		data.star = star;
		linked_list_append(stars, data);
	}
}