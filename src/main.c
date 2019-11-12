#include <stdio.h>
#include <MLV/MLV_all.h>
#include "../include/linked_list.h"
#include "../include/view.h"


void display_stars(Linked_list linked_list, MLV_Image *image) {
	Element *last = linked_list.last;
	while(last->null == 0){
		MLV_draw_image(image, last->data.star.x, last->data.star.y);
		last=last->prev;
	}
}

int main(int argc, char const *argv[])
{

	open_new_window();
	MLV_Image *image;
	image = MLV_load_image("src/media/star.png");
	MLV_resize_image(image, 30, 30);
	Linked_list stars = linked_list_create();
	int quit = 0;

	while (!quit) {
		int random_x = MLV_get_random_integer(-10, get_window_width());
		int random_speed = MLV_get_random_integer(1, 5);
		Star star = star_create(random_x, -10, 30, random_speed);
		Data data;
		data.star = star;
		linked_list_append(&stars, data);

		linked_list_stars_move_down(&stars, get_window_height());
		display_stars(stars, image);
		MLV_actualise_window();
	}
	
	MLV_wait_seconds(2);
	linked_list_free(&stars);
	close_image(image);
	close_window();
	return 0;
}