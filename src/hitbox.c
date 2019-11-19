
#include "../include/hitbox.h"
#include <stdio.h>
#include <stdlib.h>

Hitbox get_hitbox(char *path) {
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
    }
  	fclose(file);

    Hitbox hitbox = { size, rectangles };
    return hitbox;
}