#include <MLV/MLV_all.h>
#include <stdio.h>
#include "../include/linked_list.h"

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



/* Display number of FPS. */
void display_fps() {
	int fps = MLV_get_frame_rate();
	MLV_draw_text(10, 10, "FPS: %d", MLV_COLOR_RED, fps);
}
void display_health_bar(MLV_Image *image, int health) {
	int i;
	for (i = 0; i < health; i++) {
		MLV_draw_image(image, 30*i, get_window_height()-30);
	}
}
void display_stars(Linked_list linked_list, MLV_Image *image_star) {
	Element *last = linked_list.last;
	while (last->null == 0){
		MLV_draw_image(image_star, last->data.star.x, last->data.star.y);
		last=last->prev;
	}
}

void display_one_frame(MLV_Image *image_star, MLV_Image *image_heart, Linked_list linked_list, int health) {
	display_stars(linked_list, image_star);
	display_fps();
	display_health_bar(image_heart, health);
	MLV_actualise_window();
}