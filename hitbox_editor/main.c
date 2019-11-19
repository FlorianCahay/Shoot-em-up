#include <MLV/MLV_all.h>

typedef struct 
{
	float x;
	float y;
	float x2;
	float y2;
}Rectangle;


void remove_rectangle(int * nb_rectangles){
	if(*nb_rectangles>0){
		*nb_rectangles-=1;
	}	
}

void add_rectangle(Rectangle rectangles[],int * nb_rectangles,Rectangle rectangle){
	rectangles[*nb_rectangles]=rectangle;
	*nb_rectangles+=1;
}

void validate(Rectangle rectangles[],int nb_rectangles,int width,int height, MLV_Image * image,char picture_name[]){
	FILE * file;
	char file_name[50]="../src/hitbox/";
	strcat(file_name,picture_name);
	strcat(file_name ,"_hitbox.txt");
   	file = fopen (file_name,"w");
   	fprintf(file, "%d\n",nb_rectangles);
	int i;
	for (i = 0; i < nb_rectangles; ++i)
	{
		fprintf (file, "%f %f %f %f\n",rectangles[i].x,rectangles[i].y,rectangles[i].x2,rectangles[i].y2);
		MLV_draw_rectangle_on_image(width*rectangles[i].x,height*rectangles[i].y,width*rectangles[i].x2-width*rectangles[i].x,height*rectangles[i].y2-height*rectangles[i].y,MLV_COLOR_GREEN,image);
	}
  	fclose (file);
  	char path[100]="../src/media/";
  	strcat(path,picture_name);
  	strcat(path,"_hitbox.png");
   	MLV_save_image_as_bmp (image,path);
}

void draw_rectangles(Rectangle rectangles[],int nb_rectangles, int width, int height){
	

	int i;
	for (i = 0; i < nb_rectangles; ++i)
	{
		MLV_draw_rectangle(width*rectangles[i].x,height*rectangles[i].y,width*rectangles[i].x2-width*rectangles[i].x,height*rectangles[i].y2-height*rectangles[i].y,MLV_COLOR_GREEN);
	}
	MLV_actualise_window();
}



int main(int argc, char const *argv[])
{
	MLV_create_window("hitbox","hitbox",4,4);
	char picture_name[50];
	printf("Please a picture name :\n");
	scanf("%s",picture_name);
	printf("%s\n",picture_name );
	char png_name[100]="../src/media/";
	strcat(png_name,picture_name);
	strcat(png_name ,".png");
	MLV_Image * image = MLV_load_image(png_name);
	int width = MLV_get_image_width(image);
	int height=MLV_get_image_height(image);
	MLV_change_window_size(width,height);
	MLV_draw_image(image,0,0);
	MLV_actualise_window();
	Rectangle rectangles[10];
	int nb_rectangles=0;
	int choice=1;
	while(choice!=0){
		printf("0 : leave\n1 : add a Rectangle \n2 : remove last rectangle\n3 : validate \nChose a value : ");
		scanf("%d",&choice);
		printf("\n");
		switch(choice){
			case 1 :
				if(nb_rectangles>9){
					break;
				}
				Rectangle rectangle;
				printf("Enter values x y x2 y2 :\n");
				scanf("%f %f %f %f",&rectangle.x,&rectangle.y,&rectangle.x2,&rectangle.y2);
				add_rectangle(rectangles,&nb_rectangles,rectangle);
				break;
			case 2 :
				remove_rectangle(&nb_rectangles);
				break;
			case 3 :
				validate(rectangles,nb_rectangles,width,height,image,picture_name);
				choice=0;
			default :
				break;
		}
		MLV_clear_window(MLV_COLOR_BLACK);
		MLV_draw_image(image,0,0);
		draw_rectangles(rectangles,nb_rectangles,width,height);
	}
	MLV_free_image(image);
	MLV_free_window();
   return 0; 
}