#include "../include/enemies.h"

#define ENEMY_WIDTH 100
#define ENEMY_HEIGHT 80
#define ENEMY_SPEED 2

void enemies_create_enemy(Linked_list *enemies, int window_width){
	if (rand()%40 == 0) {
		Data data;
		data.spaceship=spaceship_create(MLV_get_random_integer(0, window_width-ENEMY_WIDTH),0-ENEMY_HEIGHT);
		linked_list_append(enemies,data);
	}
}

void enemies_move_down(Linked_list *enemies, int window_height) {
	Element *last = enemies->last;
	while (last->null == 0) {
		spaceship_move(&last->data.spaceship.y, +1, ENEMY_SPEED);
		if(last->data.spaceship.y>window_height){
			linked_list_remove(last);
		}
		last = last->prev;
	}
}

int get_enemy_width(){
	return ENEMY_WIDTH;
}

int get_enemy_height(){
	return ENEMY_HEIGHT;
}

int get_enemy_speed(){
	return ENEMY_SPEED;
}