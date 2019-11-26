#include "../include/view.h"

#define BLOC_WIDTH get_window_width()/10
#define BLOC_HEIGHT get_window_height()/10
#define WINDOW_WIDTH (MLV_get_desktop_height()/10)*8
#define WINDOW_HEIGHT MLV_get_desktop_width()/3

/* Return window height. */
int get_window_height() {
	return WINDOW_WIDTH;
}
/* Return window width. */
int get_window_width() {
	return WINDOW_HEIGHT;
}
/* Open window. */
void open_new_window() {
	MLV_create_window("Shoot'em up", "Shoot'em up", get_window_width(), get_window_height());
}
/* Close and free window. */
void close_window() {
	MLV_free_window();
}
/* Load image in memory. */
MLV_Image* load_image(const char *image_name) {
	return MLV_load_image(image_name);
}
/* Close and free image in memory. */
void close_image(MLV_Image *image) {
	MLV_free_image(image);
}
/* Close and free all images opened. */
void close_all_images(Images images) {
	close_image(images.star);
	close_image(images.spaceship);
	close_image(images.heart);
	close_image(images.shot_ally);
	close_image(images.shot_enemy);
	close_image(images.enemy);
}
/* Display number of FPS on the top corner left. */
void display_fps() {
	int fps = MLV_get_frame_rate();
	MLV_draw_text(10, 10, "FPS: %d", MLV_COLOR_RED, fps);
}
/* Display the health bar at the bottom left. */
void display_health_bar(MLV_Image *image, const int health) {
	int i;
	for (i = 0; i < health; i++) {
		MLV_draw_image(image, 30*i, get_window_height()-30);
	}
}
/* Display all stars. */
void display_stars(Linked_list stars, MLV_Image *image_star) {
	Element *last = stars.last;
	while (last->null == 0){
		MLV_Image * image_star_copy = MLV_copy_image(image_star);
		MLV_resize_image(image_star_copy, last->data.star.size, last->data.star.size);
		MLV_draw_image(image_star_copy, last->data.star.x, last->data.star.y);
		MLV_free_image(image_star_copy);
		image_star_copy = NULL;
		last = last->prev;
	}
}
/* Display spaceship in the center. */
void display_spaceship(MLV_Image *image_spaceship, Spaceship spaceship) {
	MLV_draw_image(image_spaceship, spaceship.x, spaceship.y);
}
/* Display all shots. */
void display_shots(MLV_Image *image_shot_ally, MLV_Image *image_shot_enemy, Linked_list shots) {
	Element *last = shots.last;
	while (last->null == 0) {
		if (last->data.shot.type == ALLY) {
			MLV_draw_image(image_shot_ally, last->data.shot.x, last->data.shot.y);	
		} else if (last->data.shot.type == ENEMY) {
			MLV_Image * image_shot_copy = MLV_copy_image(image_shot_enemy);
			MLV_rotate_image(image_shot_copy,last->data.shot.rotation+90);
			MLV_draw_image(image_shot_copy, last->data.shot.x, last->data.shot.y);
			MLV_free_image(image_shot_copy);
			image_shot_copy=NULL;
		}
		last = last->prev;
	}
}

/* Display all enemies. */
void display_enemies(MLV_Image *image_enemy, Linked_list enemies) {
	Element *last = enemies.last;
	while (last->null == 0) {
		MLV_draw_image(image_enemy, last->data.spaceship.x, last->data.spaceship.y);
		last = last->prev;
	}
}
/* Display all items in the window and actualize it. */
void display_one_frame(Images images, Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, const int health) {
	MLV_clear_window(MLV_COLOR_BLACK);
	display_stars(stars, images.star);
	display_shots(images.shot_ally, images.shot_enemy, shots);
	display_spaceship(images.spaceship,spaceship);
	display_enemies(images.enemy,enemies);
	display_fps();
	display_health_bar(images.heart, health);
	MLV_actualise_window();
}
/* Display menu */
void display_menu(MLV_Font* font_title, MLV_Font* font_choice, Linked_list stars, Images images, const int screen) {
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
/* Display a defeat message. */
void display_defeat(MLV_Font* font) {
	int text_width = 0, text_height = 0;
	MLV_get_size_of_text_with_font("DEFEAT", &text_width, &text_height, font);
	MLV_draw_text_with_font((BLOC_WIDTH*5)-(text_width/2), (BLOC_HEIGHT*5)-(text_height/2), "DEFEAT", font, MLV_COLOR_RED);
	MLV_actualise_window();
}