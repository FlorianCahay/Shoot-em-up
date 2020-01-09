/*Manage hitbox functions */ 
#include "../include/hitbox.h"
#include "../include/animation.h"
#include <stdio.h>
#include <stdlib.h>

static int box_in_box(const int x1, const int y1, const int width1, const int height1, const int x2, const int y2, const int width2, const int height2);

/*Return a Hitbox for the file path given */
Hitbox get_hitbox(char *path, const int element_width, const int element_height)
{
    int size;
    FILE * file;
    file = fopen(path, "r"); /*Open the file */
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file for get_hitbox: %s\n", path);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &size); /*Get the rectangles number */

    Rectangle *rectangles = malloc(size* sizeof(Rectangle));
    int i;
    for (i = 0; i < size; ++i)
    { /*Read each value in the file */
        fscanf(file, "%f %f %f %f", &rectangles[i].x, &rectangles[i].y, &rectangles[i].x2, &rectangles[i].y2);
        rectangles[i].x = rectangles[i].x * element_width;
        rectangles[i].x2 = rectangles[i].x2 * element_width;
        rectangles[i].y = rectangles[i].y * element_height;
        rectangles[i].y2 = rectangles[i].y2 * element_height;
    }
    fclose(file);

    Hitbox hitbox = { size, rectangles
    };
    return hitbox;
}
/*Add x and y values to each rectangle coordinates */
Rectangle rectangle_translate(Rectangle rectangle, const int x, const int y)
{
    rectangle.x += x;
    rectangle.x2 += x;
    rectangle.y += y;
    rectangle.y2 += y;
    return rectangle;
}
/*If box is in a box return 1, return 0 otherwise */
static int box_in_box(const int x1, const int y1, const int width1, const int height1, const int x2, const int y2, const int width2, const int height2)
{
    if (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2)
    {
        return 1;
    }
    return 0;
}
/*If a rectangle1 is in a rectangle2 return 1, return 0 otherwise */
int rectangle_in_rectangle(Rectangle rectangle1, const int x1, const int y1, Rectangle rectangle2, const int x2, const int y2)
{
    rectangle1 = rectangle_translate(rectangle1, x1, y1);
    rectangle2 = rectangle_translate(rectangle2, x2, y2);

    if (box_in_box(rectangle1.x, rectangle1.y,
            rectangle1.x2 - rectangle1.x, rectangle1.y2 - rectangle1.y,
            rectangle2.x, rectangle2.y,
            rectangle2.x2 - rectangle2.x, rectangle2.y2 - rectangle2.y))
    {
        return 1;
    }
    return 0;
}
/*Loop over ally shot to see if they hitted an enemy */
void shot_hit_enemy(Hitbox hitbox_enemy, Hitbox hitbox_shot_ally, Linked_list *enemies, Linked_list *shots, int *score, Linked_list *animations, MLV_Animation *animation)
{
    Element *shot = shots->last;
    while (shot->null == 0)
    { /*Loop over shots */
        if (shot->data.shot.type == ENEMY)
        { /*If not an ally shot */
            shot = shot->prev;
            continue;
        }
        Element *enemy = enemies->last;
        while (enemy->null == 0)
        { /*Loop over enemies */
            int i, j;
            if (box_in_box(shot->data.shot.x, shot->data.shot.y, get_shot_size(), get_shot_size(), enemy->data.spaceship.x, enemy->data.spaceship.y, get_enemy_width(), get_enemy_height()))
            {
                for (i = 0; i < hitbox_enemy.size; ++i)
                {
                    for (j = 0; j < hitbox_shot_ally.size; ++j)
                    {
                        if (rectangle_in_rectangle(hitbox_enemy.rectangle[i], enemy->data.spaceship.x, enemy->data.spaceship.y, hitbox_shot_ally.rectangle[j], shot->data.shot.x, shot->data.shot.y))
                        {               /*If shot hitted the enemy */
                            MLV_Animation_player *player = MLV_create_animation_player(animation);
                            Animation animation = { 0, 20, enemy->data.spaceship.x - 30, enemy->data.spaceship.y, player
                            };
                            Data data;
                            data.animation = animation;
                            linked_list_append(animations, data);
                            linked_list_remove(shot);
                            linked_list_remove(enemy);
                            *score = *score + 25;
                        }
                    }
                }
            }
            if (enemy->null == 0)
            {
                enemy = enemy->prev;
            }
        }
        if (shot->null == 0)
        {
            shot = shot->prev;
        }
    }
}
/*Loop over enemies to see if the spaceship hitted an enemy */
void spaceship_hit_enemy(Hitbox hitbox_spaceship, Hitbox hitbox_enemy, Spaceship spaceship, Linked_list *enemies, int *health, Linked_list *animations, MLV_Animation *animation)
{
    Element *enemy = enemies->last;
    while (enemy->null == 0)
    { /*Loop over enemies */
        int i, j;
        if (box_in_box(enemy->data.spaceship.x, enemy->data.spaceship.y, get_enemy_width(), get_enemy_height(), spaceship.x, spaceship.y, get_spaceship_width(), get_spaceship_height()))
        {
            for (i = 0; i < hitbox_enemy.size; ++i)
            {
                for (j = 0; j < hitbox_spaceship.size; ++j)
                {
                    if (rectangle_in_rectangle(hitbox_enemy.rectangle[i], enemy->data.spaceship.x, enemy->data.spaceship.y, hitbox_spaceship.rectangle[j], spaceship.x, spaceship.y))
                    {           /*If spaceship hitted an enemy */
                        MLV_Animation_player *player = MLV_create_animation_player(animation);
                        Animation animation = { 0, 20, enemy->data.spaceship.x - 30, enemy->data.spaceship.y, player
                        };
                        Data data;
                        data.animation = animation;
                        linked_list_append(animations, data);
                        linked_list_remove(enemy);
                        -- *health;
                    }
                }
            }
        }
        if (enemy->null == 0)
        {
            enemy = enemy->prev;
        }
    }
}
/*Loop over enemy shots to see if a shot hitted the spaceship */
void spaceship_hit_shot(Hitbox hitbox_spaceship, Hitbox hitbox_shot_enemy, Spaceship spaceship, Linked_list *shots, int *health)
{
    Element *shot = shots->last;
    while (shot->null == 0)
    { /*Loop over shots */
        if (shot->data.shot.type == ALLY)
        { /*If not an enemy shot */
            shot = shot->prev;
            continue;
        }
        int i, j;
        if (box_in_box(shot->data.shot.x, shot->data.shot.y, get_shot_size(), get_shot_size(), spaceship.x, spaceship.y, get_spaceship_width(), get_spaceship_height()))
        {
            for (i = 0; i < hitbox_shot_enemy.size; ++i)
            {
                for (j = 0; j < hitbox_spaceship.size; ++j)
                {
                    if (rectangle_in_rectangle(hitbox_shot_enemy.rectangle[i], shot->data.shot.x, shot->data.shot.y, hitbox_spaceship.rectangle[j], spaceship.x, spaceship.y))
                    {           /*If shot hitted the spaceship */
                        linked_list_remove(shot);
                        -- *health;
                    }
                }
            }
        }
        if (shot->null == 0)
        {
            shot = shot->prev;
        }
    }
}

/*Free rectangle memory */
void hitbox_free(Rectangle *rectangle)
{
    free(rectangle);
    rectangle = NULL;
}