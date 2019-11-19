
#include "../include/hitbox.h"
#include <stdio.h>
#include <stdlib.h>

Hitbox get_hitbox(char *path,int element_width,int element_height) {
    int size;
    FILE *file;
  	file = fopen(path, "r");
    if (file == NULL) {
        printf("Could not open file for get_hitbox\n") ;
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", &size);
    Rectangle *rectangles = malloc(size*sizeof(Rectangle));
    int i;
    for (i = 0; i < size; ++i)
    {
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

void rectangle_show(Rectangle rectangle){
    printf("%f %f %f %f\n",rectangle.x,rectangle.y,rectangle.x2,rectangle.y2);
}

Rectangle rectangle_translate(Rectangle rectangle,int x,int y){
    rectangle.x+=x;
    rectangle.x2+=x;
    rectangle.y+=y;
    rectangle.y2+=y;
    return rectangle;
}



int box_in_box(int x1,int y1,int width1,int height1,int x2,int y2,int width2,int height2){
    if(x1<x2+width2 && x1+width1>x2 && y1<y2+height2 && y1+height1>y2){
        return 1;
    }
    return 0;
}

void shot_hit_enemy(Hitbox hitbox_enemy,Hitbox hitbox_shot_ally,Linked_list * enemies,Linked_list * shots){
    Element * last_shot = shots->last;
    while(last_shot->null==0){
        if(last_shot->data.shot.type==ENEMY){
            last_shot=last_shot->prev;
            continue;
        }
        Element * last_enemy = enemies->last;
        while(last_enemy->null==0){
            int i,j;
            for ( i = 0; i < hitbox_enemy.size; ++i)
            {
                for (j= 0; j < hitbox_shot_ally.size; ++j)
                {
                    /*+15 ?*/
                    Rectangle rectangle_enemy=rectangle_translate(hitbox_enemy.rectangle[i],last_enemy->data.spaceship.x+15,last_enemy->data.spaceship.y);
                    Rectangle rectangle_shot=rectangle_translate(hitbox_shot_ally.rectangle[j],last_shot->data.shot.x,last_shot->data.shot.y);
                    
                    if(box_in_box(rectangle_enemy.x,rectangle_enemy.y,
                                  rectangle_enemy.x2-rectangle_enemy.x,rectangle_enemy.y2-rectangle_enemy.y,
                                  rectangle_shot.x,rectangle_shot.y,
                                  rectangle_shot.x2-rectangle_shot.x,rectangle_shot.y2-rectangle_shot.y
                                 ) )
                    {
                       linked_list_remove(last_shot);
                       linked_list_remove(last_enemy);
                    }
                }
            }
            last_enemy=last_enemy->prev;
        }  
        last_shot=last_shot->prev;
    }
}