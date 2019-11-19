
#include "../include/hitbox.h"
#include <stdio.h>
#include <stdlib.h>

Rectangle * get_hitbox(char * path){

    FILE * file;
  	int nb_rectangles;

  	file=fopen(path, "r");
    if(file==NULL)
    {
        printf( "Could not open file for get_hitbox\n" ) ;
        exit(EXIT_FAILURE);
    }
    fscanf(file,"%d",&nb_rectangles);
    Rectangle * rectangles = malloc(nb_rectangles*sizeof(Rectangle));
    int i;
    for ( i = 0; i < nb_rectangles; ++i)
    {
    	fscanf(file,"%f %f %f %f",&rectangles[i].x,&rectangles[i].y,&rectangles[i].x2,&rectangles[i].y2);
      
    }

  	fclose(file);

    return rectangles;
}