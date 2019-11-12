#include <MLV/MLV_all.h>
#include <stdio.h>

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
void close_image(MLV_Image *image) {
	MLV_free_image(image);
}
/* Close window. */
void close_window() {
	MLV_free_window();
}