#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../include/view.h"
#include "../include/main.h"
#include "../include/stars.h"
#include "../include/spaceship.h"

#define BILLION 1E9

int main(int argc, char const *argv[])
{
	/* Frame 
	struct timespec request_start, request_end;
	double accum;*/

	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;

	open_new_window();
	MLV_Image *image_star, *image_heart;
	image_star = MLV_load_image("src/media/star.png");
	image_heart = MLV_load_image("src/media/heart.png");
	MLV_resize_image(image_star, 30, 30);
	MLV_resize_image(image_heart, 30, 30);
	Linked_list stars = linked_list_create();
	int quit = 0;

	MLV_change_frame_rate(120);

	Spaceship spaceship = spaceship_create(get_window_width()/2+get_spaceship_width()/2,get_window_height()/2+get_spaceship_height()/2);

	/* Main loop */
	while (!quit) {
		/* Start frame 
		clock_gettime(CLOCK_REALTIME, &request_start);
		*/

		/* Display of the current frame */
		display_one_frame(image_star, image_heart, stars, 3);

		/* Get event */
		MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		/* Event resolution */
		if (symbol!=MLV_KEYBOARD_NONE) {
			switch(symbol){
				case MLV_KEYBOARD_LEFT :
					spaceship_move_left(&spaceship);
					break;
				case MLV_KEYBOARD_RIGHT :
					spaceship_move_right(&spaceship,get_window_width());
					break;
				case MLV_KEYBOARD_UP :
					spaceship_move_up(&spaceship);
					break;
				case MLV_KEYBOARD_DOWN :
					spaceship_move_down(&spaceship,get_window_height());
					break;
				case MLV_KEYBOARD_ESCAPE :
					quit=1;
					break;
				default :
					break;
			}
			if(state==MLV_RELEASED){
				symbol=MLV_KEYBOARD_NONE;
			}
		}
		/*show coordinates of the spaceship*/
		spaceship_show(spaceship);

		/*add a star to the stars list*/
		stars_create_star(&stars,get_window_width());

		/* Moves of the entities on the board */
		stars_move_down(&stars, get_window_height());

		/* End frame 
		clock_gettime(CLOCK_REALTIME, &request_end);
		accum = (request_end.tv_sec - request_start.tv_sec) + ((request_end.tv_nsec - request_start.tv_nsec)/BILLION);
		if (accum < (1.0/68.0)) {
			MLV_wait_milliseconds((int) (((1.0/68.0)-accum)*1000));
		}*/

		MLV_delay_according_to_frame_rate();
	}
	linked_list_free(&stars);
	close_image(image_star);
	close_image(image_heart);
	close_window();
	return 0;
}