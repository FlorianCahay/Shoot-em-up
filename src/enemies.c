/*Manage enemies list and enemies values */ 
#include "../include/enemies.h"
#include "../include/shots.h"
#define ENEMY_WIDTH 60
#define ENEMY_HEIGHT 80
#define ENEMY_SPEED 1

/*Add an enemy in the enemies list if rand() give an even number */
void enemies_create_enemy(Linked_list *enemies, const int window_width)
{
	if (rand() % 2 == 0)
	{
		Data data;
		data.spaceship = spaceship_create(MLV_get_random_integer(0, window_width - ENEMY_WIDTH), 0 - ENEMY_HEIGHT); /*initialize union*/
		linked_list_append(enemies, data);
	}
}
/*Move all enemies down */
void enemies_move_down(Linked_list *enemies, const int window_height, int *health)
{
	Element *enemy = enemies->last;
	while (enemy->null == 0)
	{ /*Loop over enemies */
		spaceship_move(&enemy->data.spaceship.y, +1, ENEMY_SPEED);
		if (enemy->data.spaceship.y > window_height)
		{ /*If enemy out of screen */
			linked_list_remove(enemy);
			*health = *health - 1;
			break;
		}
		if (enemy->null == 0)
		{
			enemy = enemy->prev;
		}
	}
}
/*Create a shot on spawning from each enemy */
void enemies_create_shot(Linked_list *enemies, Linked_list *shots, const Spaceship spaceship)
{
	Element *enemy = enemies->last;
	while (enemy->null == 0)
	{ /*Loop over enemies */
		shots_create_shot(shots, enemy->data.spaceship, get_enemy_width(), get_enemy_height(), spaceship, ENEMY);
		enemy = enemy->prev;
	}
}

int get_enemy_width()
{
	return ENEMY_WIDTH;
}

int get_enemy_height()
{
	return ENEMY_HEIGHT;
}

int get_enemy_speed()
{
	return ENEMY_SPEED;
}