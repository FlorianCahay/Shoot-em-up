#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

int get_window_height();
int get_window_width();
void open_new_window();
void close_window();
MLV_Image* load_image(const char *image_name);
void close_image(MLV_Image *image);
void display_fps();

#endif