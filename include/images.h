#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <MLV/MLV_all.h>

/* Stock each image */
typedef struct {
	MLV_Image *star;
	MLV_Image *spaceship;
	MLV_Image *heart;
	MLV_Image *shot_ally;
	MLV_Image *shot_enemy;
	MLV_Image *enemy;
} Images;

#endif