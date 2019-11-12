#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../include/linked_list.h"
#include "../include/view.h"
#include "../include/main.h"

#define BILLION 1E9



int main(int argc, char const *argv[])
{
	/* Frame 
	struct timespec request_start, request_end;
	double accum;*/

	MLV_Event event;
	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;

	open_new_window();
	MLV_Image *image_star;
	image_star = MLV_load_image("src/media/star.png");
	MLV_resize_image(image_star, 30, 30);
	Linked_list stars = linked_list_create();
	int quit = 0;

	MLV_change_frame_rate(120);

	/* Main loop */
	while (!quit) {
		/* Start frame 
		clock_gettime(CLOCK_REALTIME, &request_start);
		*/

		/* Display of the current frame */
		display_stars(stars, image_star);
		display_fps();
		MLV_actualise_window();

		/* Get event */
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		/* Event resolution */
		if (event == MLV_KEY) {
			if (state == MLV_PRESSED) {
				if (symbol == MLV_KEYBOARD_ESCAPE) {
					break;
				}
			}
		}
		create_scrolling_star(&stars, image_star);

		/* Moves of the entities on the board */
		linked_list_stars_move_down(&stars, get_window_height());

		/* End frame 
		clock_gettime(CLOCK_REALTIME, &request_end);
		accum = (request_end.tv_sec - request_start.tv_sec) + ((request_end.tv_nsec - request_start.tv_nsec)/BILLION);
		if (accum < (1.0/68.0)) {
			MLV_wait_milliseconds((int) (((1.0/68.0)-accum)*1000));
		}*/

		MLV_delay_according_to_frame_rate();
	}
	
	MLV_wait_seconds(2);
	linked_list_free(&stars);
	close_image(image_star);
	close_window();
	return 0;
}

void display_stars(Linked_list linked_list, MLV_Image *image_star) {
	Element *last = linked_list.last;
	while (last->null == 0){
		MLV_draw_image(image_star, last->data.star.x, last->data.star.y);
		last=last->prev;
	}
}

void create_scrolling_star(Linked_list *stars, MLV_Image *image_star) {
	if (rand()%4 == 0) {
		int random_x = MLV_get_random_integer(-30, get_window_width());
		int random_speed = MLV_get_random_integer(1, 5);
		/*
		int random_size = MLV_get_random_integer(20, 30);
		MLV_resize_image(image_star, random_size, random_size);
		*/
		Star star = star_create(random_x, -30, 30, random_speed);
		Data data;
		data.star = star;
		linked_list_append(stars, data);
	}
}