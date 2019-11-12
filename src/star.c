typedef struct {
	int x;
	int y;
	int size;
	int speed;
} Star;

Star star_create(int x, int y, int size, int speed){
	Star star = {};
	star.x=x;
	star.y=y;
	star.size=size;
	star.speed=speed;
	return star;
}

int star_move_down(Star * star,int window_height){
	star->y+=star->speed*1;
	if(star->y>window_height){
		return 1;
	}
	return 0;
}