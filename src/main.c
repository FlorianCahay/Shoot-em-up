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
#include "../include/data.h"

int main(int argc, char	const *argv[])
{
	char path[30];
	strcpy(path, argv[0]);
	open_new_window();
	MLV_change_frame_rate(120);
	/*Initialisation of some variables for the menu display */
	MLV_Keyboard_button symbol = MLV_KEYBOARD_NONE;
	MLV_Button_state state;
	MLV_Event event;
	int play = 0, menu = 1, quit = 0, health = 3, score = 0, timer_shot = 0, timer_enemy = 0, timer_shot_enemy = 0, wait=0;
	Data_Game data_game = init_data_game(path);

	/*Display menu */
	while (!play)
	{
		display_menu(data_game.fonts.menu_title, data_game.fonts.menu_choices, data_game.lists.stars, data_game.images, menu);
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
		switch (symbol)
		{
			case MLV_KEYBOARD_p:
				/*PLAY */
				play = 1;
				break;
			case MLV_KEYBOARD_h:
				/*HELP */
				menu = 2;
				break;
			case MLV_KEYBOARD_m:
				/*	HOME */
				menu = 1;
				break;
			case MLV_KEYBOARD_q:
				play = 1;
				quit = 1;
				break;
			default:
				break;
		}
		/*Moving stars */
		stars_create_star(&(data_game.lists.stars), get_window_width());
		stars_move_down(&(data_game.lists.stars), get_window_height());
		MLV_delay_according_to_frame_rate();
	}

	/*Animations */
	int width_animation, height_animation;
	MLV_get_image_size(data_game.images.ani_destruction, &width_animation, &height_animation);
	int nb_frames = 20, nb_layers = 1, nb_channels = 0, compteur = 0, width_frame = width_animation / 5, height_frame = height_animation / 4;
	MLV_Image *frame_destruction[nb_frames];
	int ligne, col, i;
	for (ligne = 0; ligne < 4; ligne++)
	{
		for (col = 0; col < 5; col++)
		{
			frame_destruction[compteur] = MLV_copy_partial_image(data_game.images.ani_destruction, col *width_frame, ligne *height_frame, width_frame, height_frame);
			compteur++;
		}
	}
	MLV_Animation *animation = MLV_create_animation(nb_frames, nb_layers, nb_channels);
	for (i = 0; i < nb_frames; i++)
	{
		MLV_add_frame_in_animation(frame_destruction + i, NULL, 5, animation);
	}

	/*Load hitbox for images */
	Spaceship spaceship = spaceship_create(get_window_game_width() / 2 - get_spaceship_width() / 2, (get_window_game_height() / 10) *9 - get_spaceship_height());
	int start = MLV_get_time();

	/*MAIN LOOP */
	while (!quit)
	{
		/*Display of the current frame */
		display_one_frame(data_game.images, spaceship, data_game.lists.stars, data_game.lists.shots, data_game.lists.enemies, &(data_game.lists.animations), health, score, MLV_get_time() - start);
		if (health <= 0)
		{
			display_defeat(data_game.fonts.menu_title);
			quit = 1;
			wait=1;
		}
		/*Get event */
		event = MLV_get_event(&symbol, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &state);
		/*Event management */
		if (event == MLV_KEY)
		{
			if (state == MLV_PRESSED)
			{
				events_add_event(&(data_game.lists.events), symbol);
			}
			else if (state == MLV_RELEASED)
			{
				events_remove_event(&(data_game.lists.events), symbol);
			}
		}
		Element *event = data_game.lists.events.last;
		while (event->null == 0)
		{
			switch (event->data.key)
			{
				case MLV_KEYBOARD_LEFT:
					spaceship_move_left(&spaceship);
					break;
				case MLV_KEYBOARD_RIGHT:
					spaceship_move_right(&spaceship, get_window_game_width());
					break;
				case MLV_KEYBOARD_UP:
					spaceship_move_up(&spaceship);
					break;
				case MLV_KEYBOARD_DOWN:
					spaceship_move_down(&spaceship, get_window_game_height());
					break;
				case MLV_KEYBOARD_SPACE:
					if (timer_shot == 50)
					{
						shots_create_shot(&(data_game.lists.shots), spaceship, get_spaceship_width(), get_spaceship_height(), spaceship, 0);
						timer_shot = 0;
					}
					break;
				case MLV_KEYBOARD_q:
					quit = 1;
					break;
				default:
					break;
			}
			event = event->prev;
		}
		/*Create objects */
		stars_create_star(&(data_game.lists.stars), get_window_game_width());
		if (timer_enemy == 80)
		{
			enemies_create_enemy(&(data_game.lists.enemies), get_window_game_width());
			timer_enemy = 0;
		}
		if (timer_shot_enemy == 200)
		{
			enemies_create_shot(&(data_game.lists.enemies), &(data_game.lists.shots), spaceship);
			timer_shot_enemy = 0;
		}
		/*Moves of the entities on the board */
		stars_move_down(&(data_game.lists.stars), get_window_game_height());
		shots_move(&(data_game.lists.shots), get_window_game_width(), get_window_game_height());
		enemies_move_down(&(data_game.lists.enemies), get_window_game_height(), &health);
		/*Test hitbox */
		shot_hit_enemy(data_game.hitbox.enemy, data_game.hitbox.shot_ally, &(data_game.lists.enemies), &(data_game.lists.shots), &score, &(data_game.lists.animations), animation);
		spaceship_hit_enemy(data_game.hitbox.spaceship, data_game.hitbox.enemy, spaceship, &(data_game.lists.enemies), &health, &(data_game.lists.animations), animation);
		spaceship_hit_shot(data_game.hitbox.spaceship, data_game.hitbox.shot_enemy, spaceship, &(data_game.lists.shots), &health);

		/*End frame */
		if (timer_shot < 50)
		{ 
			++timer_shot;
		}
		if (timer_enemy < 80)
		{ 
			++timer_enemy;
		}
		if (timer_shot_enemy < 200)
		{ 
			++timer_shot_enemy;
		}
		MLV_delay_according_to_frame_rate();
	}
	if(wait)
	{	
		MLV_wait_seconds(3);
	}
	

	free_data(data_game);

	MLV_free_animation(animation);
	for (i = 0; i < nb_frames; i++)
	{
		MLV_free_image(frame_destruction[i]);
	}
	MLV_free_window();
	return 0;
}