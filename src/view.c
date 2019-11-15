
#include "../include/view.h"

/* Return window height. */
int get_window_height() {
	return (MLV_get_desktop_height()/10)*8;
}
/* Return window width. */
int get_window_width() {
	return MLV_get_desktop_width()/3;
}
/* Open window. */
void open_new_window() {
	MLV_create_window("Shoot'em up", "Shoot'em up", get_window_width(), get_window_height());
}
/* Load image in memory. */
MLV_Image* load_image(const char *image_name) {
	return MLV_load_image(image_name);
}
/* Close and free image in memory. */
void close_image(MLV_Image *image) {
	MLV_free_image(image);
}
/* Close and free window. */
void close_window() {
	MLV_free_window();
}
/* Display number of FPS on the top corner left. */
void display_fps() {
	int fps = MLV_get_frame_rate();
	MLV_draw_text(10, 10, "FPS: %d", MLV_COLOR_RED, fps);
}
/* Display the health bar at the bottom left. */
void display_health_bar(MLV_Image *image, int health) {
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
void display_shots(MLV_Image *image_shot, Linked_list shots) {
	Element *last = shots.last;
	while (last->null == 0) {
		MLV_draw_image(image_shot, last->data.shot.x - 15, last->data.shot.y);
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
void display_one_frame(Images images, Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, int health) {
	MLV_clear_window(MLV_COLOR_BLACK);
	display_stars(stars, images.star);
	display_shots(images.shot_ally, shots);
	display_spaceship(images.spaceship,spaceship);
	display_enemies(images.enemy,enemies);
	display_fps();
	display_health_bar(images.heart, health);
	MLV_actualise_window();
}