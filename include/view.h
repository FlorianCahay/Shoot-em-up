#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <MLV/MLV_all.h>
#include <stdio.h>
#include "../include/linked_list.h"
#include "../include/spaceship.h"
#include "../include/images.h"

int get_window_height();
int get_window_width();
void open_new_window();
void close_window();
MLV_Image* load_image(const char *image_name);
void close_image(MLV_Image *image);
void display_fps();
void display_health_bar(MLV_Image *image, int health);
void display_stars(Linked_list linked_list, MLV_Image *image_star);
void display_one_frame(Images images, Spaceship spaceship, Linked_list linked_list, int health);

#endif