#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include <MLV/MLV_all.h>
#include "../include/hitbox.h"
#include "../include/linked_list.h"

typedef struct {
	MLV_Image *star;
	MLV_Image *spaceship;
	MLV_Image *heart;
	MLV_Image *shot_ally;
	MLV_Image *shot_enemy;
	MLV_Image *enemy;
	MLV_Image *ani_destruction;
} Data_Images;

typedef struct {
	Hitbox spaceship;
	Hitbox shot_ally;
	Hitbox shot_enemy;
	Hitbox enemy;
} Data_Hitbox;

typedef struct {
	MLV_Font *menu_title;
	MLV_Font *menu_choices;
} Data_Font;

typedef struct {
	Linked_list stars;
	Linked_list animations;
	Linked_list events;
	Linked_list shots;
	Linked_list enemies;
} Data_List;

typedef struct {
	Data_Images images;
	Data_Hitbox hitbox;
	Data_Font fonts;
	Data_List lists;
} Data_Game;

Data_Game init_data_game();
void free_data(Data_Game);

#endif