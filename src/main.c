#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "../include/view.h"
#include "../include/main.h"
#include "../include/stars.h"
#include "../include/spaceship.h"
#include "../include/events.h"
#include "../include/shot.h"
#include "../include/shots.h"
#include "../include/enemies.h"

int main(int argc, char const *argv[])
{
	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_Event event;

	open_new_window();
	Images images = { 	MLV_load_image("src/media/star.png"),
						MLV_load_image("src/media/spaceship.png"),
						MLV_load_image("src/media/heart.png"),
						MLV_load_image("src/media/shot_ally.png"),
						MLV_load_image("src/media/shot_enemy.png"),
						MLV_load_image("src/media/enemy.png") };

	MLV_resize_image(images.star, 30, 30);
	MLV_resize_image(images.heart, 30, 30);
	MLV_resize_image_with_proportions(images.shot_ally, get_shot_size(), -1);
	MLV_resize_image_with_proportions(images.shot_enemy, get_shot_size(), -1);
	MLV_resize_image_with_proportions(images.spaceship, get_spaceship_width(), get_spaceship_height());
	MLV_resize_image_with_proportions(images.enemy, get_enemy_width(), -1);
	Linked_list stars = linked_list_create();
	Linked_list events = linked_list_create();
	Linked_list shots = linked_list_create();
	Linked_list enemies = linked_list_create();
	int quit = 0, health = 3, timer_shot = 0, timer_enemy = 0;

	MLV_change_frame_rate(120);

	Spaceship spaceship = spaceship_create(get_window_width()/2 + get_spaceship_width()/2, get_window_height()/2 + get_spaceship_height()/2);

	/* Main loop */
	while (!quit) {
		/* Start frame */

		/* Display of the current frame */
		display_one_frame(images, spaceship, stars, shots, enemies, health);

		/* Get event */
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);

		if (event == MLV_KEY) {
			if (state == MLV_PRESSED) {
				events_add_event(&events, symbol);
			} else if (state == MLV_RELEASED) {
				events_remove_event(&events, symbol);
			}
		}
		Element *last_event = events.last;
		while (last_event->null == 0) {
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
				case MLV_KEYBOARD_SPACE :
					if (timer_shot == 30) {
						shots_create_shot(&shots, spaceship, get_spaceship_width(), get_spaceship_height(), 0);
						timer_shot = 0;	
					}
					break;	
				case MLV_KEYBOARD_ESCAPE :
					quit = 1;
					break;
				default :
					break;
			}
			last_event = last_event->prev;
		}

		/* Create objects */
		stars_create_star(&stars, get_window_width());
		if (timer_enemy == 80) {
			enemies_create_enemy(&enemies, get_window_width());
			enemies_create_shot(&enemies, &shots);
			timer_enemy = 0;
		}

		

		/* Moves of the entities on the board */
		stars_move_down(&stars, get_window_height());
		shots_move(&shots, get_window_height());
		enemies_move_down(&enemies, get_window_height());

		

		/* End frame */
		if (timer_shot < 30) {
			++timer_shot;
		}
		if (timer_enemy < 80) {
			++timer_enemy;
		}
		MLV_delay_according_to_frame_rate();
	}

	linked_list_free(&stars);
	linked_list_free(&events);
	linked_list_free(&shots);
	linked_list_free(&enemies);
	close_image(images.star);
	close_image(images.spaceship);
	close_image(images.heart);
	close_image(images.shot_ally);
	close_image(images.shot_enemy);
	close_image(images.enemy);
	close_window();

	return 0;
}