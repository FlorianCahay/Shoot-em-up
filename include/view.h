#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <MLV/MLV_all.h>
#include <stdio.h>
#include "../include/linked_list.h"
#include "../include/spaceship.h"
#include "../include/data.h"

int get_window_height();
int get_window_width();
int get_window_game_height();
int get_window_game_width();
void open_new_window();

void display_stats(const MLV_Image *image, const int score, const int health, const int time);
void display_stars(Linked_list stars, const MLV_Image *image_star);
void display_shots(const MLV_Image *image_shot, const MLV_Image *image_shot_enemy, Linked_list shots);
void display_enemies(const MLV_Image *image_enemy, Linked_list enemies);
void display_one_frame(const Data_Images images, const Spaceship spaceship, Linked_list stars, Linked_list shots, Linked_list enemies, Linked_list *animations, const int health, const int score, const int time);

void display_menu(const MLV_Font* font, const MLV_Font* font_choice, Linked_list stars, const Data_Images images, const int screen);
void display_help(const MLV_Font* font_title, const MLV_Font* font_text);
void display_menu_bar(const MLV_Font* font_text);
void display_home(const MLV_Font* font_title, const MLV_Font* font_choice);

void display_defeat(const MLV_Font* font);

#endif