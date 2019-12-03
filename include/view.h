#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <MLV/MLV_all.h>
#include <stdio.h>
#include "../include/linked_list.h"
#include "../include/spaceship.h"
#include "../include/images.h"

int get_window_height();
int get_window_width();
int get_window_game_height();
int get_window_game_width();
void open_new_window();
void close_window();

MLV_Image* load_image(const char *image_name);
void close_image(MLV_Image *image);
void close_all_images(Images images);

void display_stats(MLV_Image *image, const int score, const int health, const int time);
void display_stars(Linked_list stars, MLV_Image *image_star);
void display_shots(MLV_Image *image_shot, MLV_Image *image_shot_enemy, Linked_list shots);
void display_enemies(MLV_Image *image_enemy, Linked_list enemies);
void display_one_frame(Images images, Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, Linked_list *animations, const int health, const int score, const int time);

void display_menu(MLV_Font* font, MLV_Font* font_choice, Linked_list stars, Images images, const int screen);
void display_help(MLV_Font* font_title, MLV_Font* font_text);
void display_menu_bar(MLV_Font* font_text);
void display_home(MLV_Font* font_title, MLV_Font* font_choice);

void display_defeat(MLV_Font* font);

#endif