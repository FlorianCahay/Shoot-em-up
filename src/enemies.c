#include "../include/enemies.h"
#include "../include/shots.h"

#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 80
#define ENEMY_SPEED 1

/* Return a enemy with all his properties set. */
void enemies_create_enemy(Linked_list *enemies, int window_width){
	if (rand()%2 == 0) {
		Data data;
		data.spaceship = spaceship_create(MLV_get_random_integer(0, window_width-ENEMY_WIDTH), 0-ENEMY_HEIGHT);
		linked_list_append(enemies, data);
	}
}
/* Move down all enemies. */
void enemies_move_down(Linked_list *enemies, int window_height,int * health) {
	Element *last = enemies->last;
	while (last->null == 0) {
		spaceship_move(&last->data.spaceship.y, +1, ENEMY_SPEED);
		if(last->data.spaceship.y > window_height){
			linked_list_remove(last);
			*health=*health-1;
		}
		last = last->prev;
	}
}
/* Enemy shot. */
void enemies_create_shot(Linked_list *enemies, Linked_list *shots,Spaceship spaceship,int window_height) {
	Element *last = enemies->last;
	while (last->null == 0) {
		shots_create_shot(shots, last->data.spaceship, get_enemy_width(), get_enemy_height(),spaceship,window_height,ENEMY);	
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