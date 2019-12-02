/* Manage hitbox functions */
#include "../include/hitbox.h"
#include <stdio.h>
#include <stdlib.h>

/* Return a Hitbox for the file path given */
Hitbox get_hitbox(char *path,int element_width,int element_height) {
    int size;
    FILE *file;
  	file = fopen(path, "r"); /* Open the file */
    if (file == NULL) {
        printf("Could not open file for get_hitbox\n") ;
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &size); /* Get the rectangles number */

    Rectangle *rectangles = malloc(size*sizeof(Rectangle));
    int i;
    for (i = 0; i < size; ++i){ /* Read each value in the file */
    	fscanf(file, "%f %f %f %f", &rectangles[i].x, &rectangles[i].y, &rectangles[i].x2, &rectangles[i].y2);
        rectangles[i].x=rectangles[i].x*element_width;
        rectangles[i].x2=rectangles[i].x2*element_width;
        rectangles[i].y=rectangles[i].y*element_height;
        rectangles[i].y2=rectangles[i].y2*element_height;
    }
  	fclose(file);

    Hitbox hitbox = { size, rectangles };
    return hitbox;
}
/* Print rectangle values */
void rectangle_show(Rectangle rectangle){
    printf("%f %f %f %f\n",rectangle.x,rectangle.y,rectangle.x2,rectangle.y2);
}
/* Add x and y values to each rectangle coordinates */
Rectangle rectangle_translate(Rectangle rectangle,int x,int y){
    rectangle.x+=x;
    rectangle.x2+=x;
    rectangle.y+=y;
    rectangle.y2+=y;
    return rectangle;
}
/* If box is in a box return 1, return 0 otherwise */
int box_in_box(int x1,int y1,int width1,int height1,int x2,int y2,int width2,int height2){
    if(x1<x2+width2 && x1+width1>x2 && y1<y2+height2 && y1+height1>y2){
        return 1;
    }
    return 0;
}
/* If a rectangle1 is in a rectangle2 return 1, return 0 otherwise */
int rectangle_in_rectangle(Rectangle rectangle1,int x1,int y1,Rectangle rectangle2,int x2,int y2){
    rectangle1=rectangle_translate(rectangle1,x1,y1);
    rectangle2=rectangle_translate(rectangle2,x2,y2);
                    
    if(box_in_box(rectangle1.x,rectangle1.y,
                  rectangle1.x2-rectangle1.x,rectangle1.y2-rectangle1.y,
                  rectangle2.x,rectangle2.y,
                  rectangle2.x2-rectangle2.x,rectangle2.y2-rectangle2.y) )
    {
        return 1;
    }
    return 0;
}
/* Loop over ally shot to see if they hitted an enemy */
void shot_hit_enemy(Hitbox hitbox_enemy, Hitbox hitbox_shot_ally, Linked_list *enemies, Linked_list *shots, int *score){
    Element *last_shot = shots->last;
    while (last_shot->null == 0){ /* Loop over shots */
        if (last_shot->data.shot.type == ENEMY) { /* If not an ally shot */
            last_shot = last_shot->prev;
            continue;
        }
        Element *last_enemy = enemies->last;
        while (last_enemy->null == 0) { /* Loop over enemies */
            int i,j;
            for (i = 0; i < hitbox_enemy.size; ++i)
            {
                for (j= 0; j < hitbox_shot_ally.size; ++j)
                { 
                    if (rectangle_in_rectangle(hitbox_enemy.rectangle[i], last_enemy->data.spaceship.x, last_enemy->data.spaceship.y, hitbox_shot_ally.rectangle[j], last_shot->data.shot.x, last_shot->data.shot.y)) {
                        /* If shot hitted the enemy */
                        linked_list_remove(last_shot);
                        linked_list_remove(last_enemy);
                        *score = *score + 25;
                    }
                }
            }
            if(last_enemy->null==0){
                last_enemy=last_enemy->prev;
            }
        }  
        if(last_shot->null==0){
            last_shot=last_shot->prev;
        }
    }
}
/* Loop over enemies to see if the spaceship hitted an enemy */
void spaceship_hit_enemy(Hitbox hitbox_spaceship,Hitbox hitbox_enemy,Spaceship spaceship,Linked_list * enemies,int * health){
    Element * last_enemy = enemies->last;
    while(last_enemy->null==0){ /* Loop over enemies */
        int i,j;
            for ( i = 0; i < hitbox_enemy.size; ++i)
            {
                for (j= 0; j < hitbox_spaceship.size; ++j)
                {
                    if(rectangle_in_rectangle(hitbox_enemy.rectangle[i],last_enemy->data.spaceship.x,last_enemy->data.spaceship.y,hitbox_spaceship.rectangle[j],spaceship.x,spaceship.y)){
                        /* If spaceship hitted an enemy */
                        linked_list_remove(last_enemy);
                        --*health;
                    }
                }
            }
        if(last_enemy->null==0){
            last_enemy=last_enemy->prev;
        }
    }
}
/* Loop over enemy shots to see if a shot hitted the spaceship */
void spaceship_hit_shot(Hitbox hitbox_spaceship,Hitbox hitbox_shot_enemy,Spaceship spaceship,Linked_list * shots,int * health){
    Element * last_shot = shots->last;
    while(last_shot->null==0){ /* Loop over shots */
        if(last_shot->data.shot.type==ALLY){ /* If not an enemy shot */
            last_shot=last_shot->prev;
            continue;
        }
        int i,j;
            for ( i = 0; i < hitbox_shot_enemy.size; ++i)
            {
                for (j= 0; j < hitbox_spaceship.size; ++j)
                {
                    if(rectangle_in_rectangle(hitbox_shot_enemy.rectangle[i],last_shot->data.shot.x,last_shot->data.shot.y,hitbox_spaceship.rectangle[j],spaceship.x,spaceship.y)){
                        /* If shot hitted the spaceship */
                        linked_list_remove(last_shot);
                        --*health;
                    }
                }
            }
        if(last_shot->null==0){
            last_shot=last_shot->prev;
        }
    }
}

/* Free rectangle memory */
void hitbox_free(Rectangle * rectangle){
    free(rectangle);
    rectangle=NULL;
}