#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "../include/animation.h"
#include "../include/view.h"
#include "../include/main.h"
#include "../include/stars.h"
#include "../include/spaceship.h"
#include "../include/events.h"
#include "../include/shot.h"
#include "../include/shots.h"
#include "../include/enemies.h"
#include "../include/hitbox.h"

int main(int argc, char const *argv[])
{
	open_new_window();
	MLV_change_frame_rate(120);

	/* Initialisation of some variables for the menu display */
	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_Event event;
	MLV_Font* font_title = MLV_load_font("src/fonts/Orbitron-Bold.ttf", 50);
	MLV_Font* font_choice = MLV_load_font("src/fonts/Orbitron-Regular.ttf", 25);
	int play = 0, menu = 1, quit = 0, health = 3, score = 0, timer_shot = 0, timer_enemy = 0, timer_shot_enemy = 0;
	Images images = { 	MLV_load_image("src/media/star.png"),
						MLV_load_image("src/media/spaceship.png"),
						MLV_load_image("src/media/heart.png"),
						MLV_load_image("src/media/shot_ally.png"),
						MLV_load_image("src/media/shot_enemy.png"),
						MLV_load_image("src/media/enemy.png") };
	MLV_resize_image(images.star, 30, 30);
	Linked_list stars = linked_list_create();

	/* Display menu */
	while (!play) {
		display_menu(font_title, font_choice, stars, images, menu);
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
		switch (symbol) {
			case MLV_KEYBOARD_p :
				/* PLAY */
				play = 1;
				break;
			case MLV_KEYBOARD_h :
				/* HELP */
				menu = 2;
				break;
			case MLV_KEYBOARD_m :
				/*	HOME */
				menu = 1;
				break;
			case MLV_KEYBOARD_q:
				play = 1;
				quit = 1;
				break;
			default :
				break;
		}
		/* Moving stars */
		stars_create_star(&stars, get_window_width());
		stars_move_down(&stars, get_window_height());

		MLV_delay_according_to_frame_rate();
	}
	MLV_free_font(font_choice);
	
	/* Animations */
	MLV_Image *img_destruction = MLV_load_image("src/media/destruction.png");
	int width_animation, height_animation;
	MLV_get_image_size(img_destruction, &width_animation, &height_animation);
	int nb_frames = 20, nb_layers = 1, nb_channels = 0, compteur = 0, width_frame = width_animation/5, height_frame = height_animation/4;    
    MLV_Image *frame_destruction[nb_frames];
    int ligne, col, i;    
    for (ligne = 0; ligne < 4; ligne++) {
    	for (col = 0; col < 5; col++) {
    		frame_destruction[compteur] = MLV_copy_partial_image(img_destruction, col*width_frame, ligne*height_frame, width_frame, height_frame);
    		compteur++;
    	}
    }
	MLV_Animation* animation;
    animation = MLV_create_animation(nb_frames, nb_layers, nb_channels);
    for (i = 0; i < nb_frames; i++) {
    	MLV_add_frame_in_animation(frame_destruction+i, NULL, 5, animation);
    }
    MLV_Animation_player *animation_player = MLV_create_animation_player(animation);

	/* Load hitbox for images */
	Hitbox hitbox_spaceship = get_hitbox("src/hitbox/spaceship_hitbox.txt", get_spaceship_width(), get_spaceship_height());
	Hitbox hitbox_shot_ally = get_hitbox("src/hitbox/shot_ally_hitbox.txt", get_shot_size(), get_shot_size());
	Hitbox hitbox_shot_enemy = get_hitbox("src/hitbox/shot_enemy_hitbox.txt", get_shot_size(), get_shot_size());
	Hitbox hitbox_enemy =get_hitbox("src/hitbox/enemy_hitbox.txt", get_enemy_width(), get_enemy_height());
	/* Resize images */
	MLV_resize_image(images.heart, 50, 50);
	MLV_resize_image_with_proportions(images.shot_ally, get_shot_size(), -1);
	MLV_resize_image_with_proportions(images.shot_enemy, get_shot_size(), -1);
	MLV_resize_image_with_proportions(images.spaceship, get_spaceship_width(), get_spaceship_height());
	MLV_resize_image_with_proportions(images.enemy, get_enemy_width(), -1);
	/* Initialisation of other variables */
	Linked_list animations = linked_list_create();
	Linked_list events = linked_list_create();
	Linked_list shots = linked_list_create();
	Linked_list enemies = linked_list_create();
	Spaceship spaceship = spaceship_create(get_window_game_width()/2 - get_spaceship_width()/2, (get_window_game_height()/10)*9 - get_spaceship_height());
	int start = MLV_get_time();

	/* MAIN LOOP */
	while (!quit) {
		/* Display of the current frame */
		display_one_frame(images, spaceship, stars, shots, enemies, &animations, health, score, MLV_get_time()-start);
		if (health <= 0) {
			display_defeat(font_title);
			quit = 1;
		}
		/* Get event */
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
		/* Event management */
		if (event == MLV_KEY) {
			if (state == MLV_PRESSED) {
				events_add_event(&events, symbol);
			} else if (state == MLV_RELEASED) {
				events_remove_event(&events, symbol);
			}
		}
		Element *event = events.last;
		while (event->null == 0) {
			switch (event->data.key) {
				case MLV_KEYBOARD_LEFT :
					spaceship_move_left(&spaceship);
					break;
				case MLV_KEYBOARD_RIGHT :
					spaceship_move_right(&spaceship, get_window_game_width());
					break;
				case MLV_KEYBOARD_UP :
					spaceship_move_up(&spaceship);
					break;
				case MLV_KEYBOARD_DOWN :
					spaceship_move_down(&spaceship, get_window_game_height());
					break;
				case MLV_KEYBOARD_SPACE :
					if (timer_shot == 50) {
						shots_create_shot(&shots, spaceship, get_spaceship_width(), get_spaceship_height(), spaceship, get_window_game_height(), 0);
						timer_shot = 0;	
					}
					break;	
				case MLV_KEYBOARD_q :
					quit = 1;
					break;
				default :
					break;
			}
			event = event->prev;
		}
		/* Create objects */
		stars_create_star(&stars, get_window_game_width());
		if (timer_enemy == 80) {
			enemies_create_enemy(&enemies, get_window_game_width());
			timer_enemy = 0;
		}
		if (timer_shot_enemy == 200) {
			enemies_create_shot(&enemies, &shots, spaceship, get_window_game_height());
			timer_shot_enemy = 0;
		}
		/* Moves of the entities on the board */
		stars_move_down(&stars, get_window_game_height());
		shots_move(&shots, get_window_game_width(), get_window_game_height());
		enemies_move_down(&enemies, get_window_game_height(), &health);
		/* Test hitbox */
		shot_hit_enemy(hitbox_enemy, hitbox_shot_ally, &enemies, &shots, &score, &animations, animation_player);
		spaceship_hit_enemy(hitbox_spaceship, hitbox_enemy, spaceship,&enemies, &health);
		spaceship_hit_shot(hitbox_spaceship, hitbox_shot_enemy, spaceship,&shots, &health);

		/* End frame */
		if (timer_shot < 50) {
			++timer_shot;
		}
		if (timer_enemy < 80) {
			++timer_enemy;
		}
		if (timer_shot_enemy < 200) {
			++timer_shot_enemy;
		}
		MLV_delay_according_to_frame_rate();
	}
	MLV_wait_seconds(3);
	MLV_free_font(font_title);
	MLV_free_animation_player(animation_player);
    MLV_free_animation(animation);
    for (i = 0; i < nb_frames; i++) {
    	MLV_free_image(frame_destruction[i]);
    }
    MLV_free_image(img_destruction);
    linked_list_free(&animations);
	linked_list_free(&stars);
	linked_list_free(&events);
	linked_list_free(&shots);
	linked_list_free(&enemies);
	hitbox_free(hitbox_spaceship.rectangle);
	hitbox_free(hitbox_shot_enemy.rectangle);
	hitbox_free(hitbox_shot_ally.rectangle);
	hitbox_free(hitbox_enemy.rectangle);
	close_all_images(images);
	close_window();

	return 0;
}