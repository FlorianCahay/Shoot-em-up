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
void display_stars(Linked_list stars, MLV_Image *image_star);
void display_shots(MLV_Image *image_shot, MLV_Image *image_shot_enemy, Linked_list shots);
void display_enemies(MLV_Image *image_enemy, Linked_list enemies);
void display_one_frame(Images images, Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, int health);
void display_menu(MLV_Font* font, MLV_Font* font_choice, Linked_list stars, Images images);
void display_help(MLV_Font* font_title, MLV_Font* font_text);
void display_menu_bar(MLV_Font* font_text);

#endif