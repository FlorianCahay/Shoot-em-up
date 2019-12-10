/* Draw elements */
#include "../include/view.h"

#define BLOC_WIDTH get_window_width()/10
#define BLOC_HEIGHT get_window_height()/10
#define WINDOW_HEIGHT (MLV_get_desktop_height()/10)*9
#define WINDOW_WIDTH (MLV_get_desktop_width()/3)

/* Return window height. */
int get_window_height() {
	return WINDOW_HEIGHT;
}
/* Return window width. */
int get_window_width() {
	return WINDOW_WIDTH;
}
/* Return window game height. */
int get_window_game_height() {
	return WINDOW_HEIGHT-BLOC_HEIGHT;
}
/* Return window game width. */
int get_window_game_width() {
	return WINDOW_WIDTH;
}
/* Open window. */
void open_new_window() {
	MLV_create_window("Shoot'em up", "Shoot'em up", get_window_width(), get_window_height());
}
/* Display a defeat message. */
void display_defeat(MLV_Font* font) {
	int text_width = 0, text_height = 0;
	MLV_get_size_of_text_with_font("DEFEAT", &text_width, &text_height, font);
	MLV_draw_text_with_font((get_window_game_width()/2)-(text_width/2), (get_window_game_height()/2)-(text_height/2), "DEFEAT", font, MLV_COLOR_RED);
	MLV_actualise_window();
}
/* Display number of FPS on the top corner left, health bar at the bottom left and score. */
void display_stats(MLV_Image *image, const int score, const int health, const int time) {
	MLV_draw_filled_rectangle(0, get_window_game_height(), get_window_game_width(), get_window_height(), MLV_COLOR_WHITE);
	int fps = MLV_get_frame_rate();
	int i;
	for (i = 1; i < health+1; i++) {
		MLV_draw_image(image, get_window_game_width()-(i*50), get_window_game_height()+(BLOC_HEIGHT/3));
	}
	MLV_draw_text(10, 10, "FPS: %d", MLV_COLOR_RED, fps);
	MLV_draw_text(BLOC_WIDTH/2, get_window_game_height()+(BLOC_HEIGHT/3)/2, "Score: %d", MLV_COLOR_RED, score);
	MLV_draw_text(BLOC_WIDTH/2, get_window_game_height()+((BLOC_HEIGHT/3)*2)/2, "Kills: %d", MLV_COLOR_RED, score/25);
	MLV_draw_text(BLOC_WIDTH/2, get_window_game_height()+(BLOC_HEIGHT)/2, "Time: %d", MLV_COLOR_RED, time/1000);

}
/* Display all stars. */
void display_stars(Linked_list stars, MLV_Image *image_star) {
	Element *star = stars.last;
	while (star->null == 0){
		MLV_Image * image_star_copy = MLV_copy_image(image_star);
		MLV_resize_image(image_star_copy, star->data.star.size, star->data.star.size);
		MLV_draw_image(image_star_copy, star->data.star.x, star->data.star.y);
		MLV_free_image(image_star_copy);
		image_star_copy = NULL;
		star = star->prev;
	}
}
/* Display spaceship. */
void display_spaceship(MLV_Image *image_spaceship, Spaceship spaceship) {
	MLV_draw_image(image_spaceship, spaceship.x, spaceship.y);
}
/* Display all shots. */
void display_shots(MLV_Image *image_shot_ally, MLV_Image *image_shot_enemy, Linked_list shots) {
	Element *shot = shots.last;
	while (shot->null == 0) {
		if (shot->data.shot.type == ALLY) {
			MLV_draw_image(image_shot_ally, shot->data.shot.x, shot->data.shot.y);	
		} else if (shot->data.shot.type == ENEMY) {
			MLV_Image *image_shot_copy = MLV_copy_image(image_shot_enemy);
			MLV_rotate_image(image_shot_copy, shot->data.shot.rotation+90);
			MLV_draw_image(image_shot_copy, shot->data.shot.x, shot->data.shot.y);
			MLV_free_image(image_shot_copy);
			image_shot_copy = NULL;
		}
		shot = shot->prev;
	}
}
/* Display all enemies. */
void display_enemies(MLV_Image *image_enemy, Linked_list enemies) {
	Element *enemy = enemies.last;
	while (enemy->null == 0) {
		MLV_draw_image(image_enemy, enemy->data.spaceship.x, enemy->data.spaceship.y);
		enemy = enemy->prev;
	}
}
/* Display all animations. */
void display_animations(Linked_list *animations) {
	Element *animation = animations->last;
	while (animation->null == 0) {
		if ((animation->data.animation.current_frame)/5 < animation->data.animation.total_frame) {
			MLV_update_animation_player(animation->data.animation.player);
            MLV_play_animation_player(animation->data.animation.player);
            MLV_draw_image_from_animation_player(animation->data.animation.player, 0, animation->data.animation.position_x, animation->data.animation.position_y);
            animation->data.animation.current_frame += 1;
		} else {
			MLV_stop_animation_player(animation->data.animation.player);
        	MLV_rewind_animation_player(animation->data.animation.player);
        	linked_list_remove(animation);
		}
		if (animation->null == 0) {
			animation = animation->prev;
		}
	}
}
/* Display all items in the window and actualize it. */
void display_one_frame(Data_Images images, Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, Linked_list *animations, const int health, const int score, const int time) {
	MLV_clear_window(MLV_COLOR_BLACK);
	display_stars(stars, images.star);
	display_shots(images.shot_ally, images.shot_enemy, shots);
	display_spaceship(images.spaceship,spaceship);
	display_enemies(images.enemy,enemies);
	display_animations(animations);
	display_stats(images.heart, score, health, time);
	MLV_actualise_window();
}

/*** MENU ***/

/* Display menu */
void display_menu(MLV_Font* font_title, MLV_Font* font_choice, Linked_list stars, Data_Images images, const int screen) {
	MLV_clear_window(MLV_COLOR_BLACK);
	display_stars(stars, images.star);

	switch (screen) {
		case 1:
			display_home(font_title, font_choice);
			break;
		case 2:
			display_help(font_title, font_choice);
			break;
		default:
			break;
	}
	MLV_actualise_window();
}

void display_home(MLV_Font* font_title, MLV_Font* font_choice) {
	int text_title_width = 0, text_title_height = 0, text_choice_width = 0, text_choice_height = 0;
	MLV_get_size_of_text_with_font("Shoot'em up", &text_title_width, &text_title_height, font_title);
	MLV_get_size_of_text_with_font("P - Play", &text_choice_width, &text_choice_height, font_choice);
	
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_title_width/2), (BLOC_HEIGHT*3)-(text_title_height/2), "Shoot'em up", font_title, MLV_COLOR_RED);
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_choice_width/2), (BLOC_HEIGHT*5)-(text_choice_height/2), "P - Play", font_choice, MLV_COLOR_RED);
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_choice_width/2), (BLOC_HEIGHT*6)-(text_choice_height/2), "H - Help", font_choice, MLV_COLOR_RED);
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_choice_width/2), (BLOC_HEIGHT*7)-(text_choice_height/2), "Q - Quit", font_choice, MLV_COLOR_RED);
}
void display_help(MLV_Font* font_title, MLV_Font* font_text) {
	char msg[] = "Utilisez les flèches pour vous déplacer\nAppuyez sur espace pour tirer\nAppuyer sur Q pour quitter";

	int text_title_width = 0, text_title_height = 0;
	MLV_get_size_of_text_with_font("HELP", &text_title_width, &text_title_height, font_title);

	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_title_width/2), (BLOC_HEIGHT*2)-(text_title_height/2), "HELP", font_title, MLV_COLOR_RED);
	MLV_draw_adapted_text_box_with_font(BLOC_WIDTH-(BLOC_WIDTH/2), BLOC_HEIGHT*4, msg, font_text, 20, MLV_COLOR_BLACK, MLV_COLOR_RED, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
	display_menu_bar(font_text);
}

void display_menu_bar(MLV_Font* font_text) {
	int text_width = 0;
	MLV_get_size_of_text_with_font("A - AAAA", &text_width, NULL, font_text);

	MLV_draw_text_with_font((BLOC_WIDTH*2)-(text_width/2), BLOC_HEIGHT*9, "P - PLAY", font_text, MLV_COLOR_RED);
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_width/2), BLOC_HEIGHT*9, "H - HELP", font_text, MLV_COLOR_RED);
	MLV_draw_text_with_font((BLOC_WIDTH*8)-(text_width/2), BLOC_HEIGHT*9, "M - MENU", font_text, MLV_COLOR_RED);
}