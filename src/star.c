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

void star_move_down(Star * star){
	star->y+=star->speed*1;
}