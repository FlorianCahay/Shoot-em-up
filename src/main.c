#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../include/view.h"
#include "../include/main.h"
#include "../include/stars.h"
#include "../include/spaceship.h"
#include "../include/events.h"

#define BILLION 1E9

int main(int argc, char const *argv[])
{
	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_Event event;

	open_new_window();
	MLV_Image *image_star, *image_heart, *image_spaceship;
	image_star = MLV_load_image("src/media/star.png");
	image_heart = MLV_load_image("src/media/heart.png");
	image_spaceship = MLV_load_image("src/media/spaceship.png");
	MLV_resize_image(image_star, 30, 30);
	MLV_resize_image(image_heart, 30, 30);
	MLV_resize_image_with_proportions(image_spaceship, get_spaceship_width(), get_spaceship_height());
	Linked_list stars = linked_list_create();
	Linked_list events = linked_list_create();
	int quit = 0, health = 3;

	MLV_change_frame_rate(120);

	Spaceship spaceship = spaceship_create(get_window_width()/2 + get_spaceship_width()/2, get_window_height()/2 + get_spaceship_height()/2);

	/* Main loop */
	while (!quit) {
		/* Start frame */

		/* Display of the current frame */
		display_one_frame(image_star, image_heart, image_spaceship, spaceship, stars, health);

		/* Get event */
		event=MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		if(event==MLV_KEY){
			if (state==MLV_PRESSED) {
			events_add_event(&events,symbol);
			}else if (state==MLV_RELEASED) {
				events_remove_event(&events,symbol);
			}
		}
		Element * last_event = events.last;
		while(last_event->null==0){
			switch (last_event->data.key) {
				case MLV_KEYBOARD_LEFT :
					spaceship_move_left(&spaceship);
					break;
				case MLV_KEYBOARD_RIGHT :
					spaceship_move_right(&spaceship, get_window_width());
					break;
				case MLV_KEYBOARD_UP :
					spaceship_move_up(&spaceship);
					break;
				case MLV_KEYBOARD_DOWN :
					spaceship_move_down(&spaceship, get_window_height());
					break;
				case MLV_KEYBOARD_ESCAPE :
					quit = 1;
					break;
				default :
					break;
			}
			last_event=last_event->prev;
		}

		/*add a star to the stars list*/
		stars_create_star(&stars, get_window_width());

		/* Moves of the entities on the board */
		stars_move_down(&stars, get_window_height());

		/* End frame */
		MLV_delay_according_to_frame_rate();
	}

	linked_list_free(&stars);
	linked_list_free(&events);
	close_image(image_star);
	close_image(image_heart);
	close_image(image_spaceship);
	close_window();

	return 0;
}