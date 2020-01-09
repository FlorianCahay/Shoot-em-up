#include "../include/data.h"

static Data_Images init_images(const char *path);
static void free_images(Data_Images);
static Data_Hitbox init_hitbox(const char *path);
static void free_hitbox(Data_Hitbox);
static Data_Font init_fonts(const char *path);
static void free_fonts(Data_Font);
static Data_List init_lists();
static void free_lists(Data_List);
static char* get_path_data(const  char *path);

static char* get_path_data(const char* path) {
	if (strcmp(path, "./bin/project") == 0) {
		return "";
	}
	return "../";
}

/* Load images. */
static Data_Images init_images(const char *path)
{
	char path_img_star[50];
	char path_img_spaceship[50];
	char path_img_heart[50];
	char path_img_shot_ally[50];
	char path_img_shot_enemy[50];
	char path_img_enemy[50];
	char path_img_destruction[50];

	strcpy(path_img_star, path);
	strcat(path_img_star, "src/media/star.png");
	MLV_Image *image_star = MLV_load_image(path_img_star);
	if (!image_star)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_star);
		exit(1);
	}

	strcpy(path_img_spaceship, path);
	strcat(path_img_spaceship, "src/media/spaceship.png");
	MLV_Image *image_spaceship = MLV_load_image(path_img_spaceship);
	if (!image_spaceship)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_spaceship);
		exit(1);
	}

	strcpy(path_img_heart, path);
	strcat(path_img_heart, "src/media/heart.png");
	MLV_Image *image_heart = MLV_load_image(path_img_heart);
	if (!image_heart)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_heart);
		exit(1);
	}

	strcpy(path_img_shot_ally, path);
	strcat(path_img_shot_ally, "src/media/shot_ally.png");
	MLV_Image *image_shot_ally = MLV_load_image(path_img_shot_ally);
	if (!image_shot_ally)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_shot_ally);
		exit(1);
	}

	strcpy(path_img_shot_enemy, path);
	strcat(path_img_shot_enemy, "src/media/shot_enemy.png");
	MLV_Image *image_shot_enemy = MLV_load_image(path_img_shot_enemy);
	if (!image_shot_enemy)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_shot_enemy);
		exit(1);
	}

	strcpy(path_img_enemy, path);
	strcat(path_img_enemy, "src/media/enemy.png");
	MLV_Image *image_enemy = MLV_load_image(path_img_enemy);
	if (!image_enemy)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_enemy);
		exit(1);
	}

	strcpy(path_img_destruction, path);
	strcat(path_img_destruction, "src/media/destruction.png");
	MLV_Image *image_ani_destruction = MLV_load_image(path_img_destruction);
	if (!image_ani_destruction)
	{
		fprintf(stderr, "It was impossible to load the file %s.\n", path_img_destruction);
		exit(1);
	}

	MLV_resize_image(image_star, 30, 30);
	MLV_resize_image_with_proportions(image_spaceship, get_spaceship_width(), get_spaceship_height());
	MLV_resize_image(image_heart, 50, 50);
	MLV_resize_image_with_proportions(image_shot_ally, get_shot_size(), -1);
	MLV_resize_image_with_proportions(image_shot_enemy, get_shot_size(), -1);
	MLV_resize_image_with_proportions(image_enemy, get_enemy_width(), -1);

	Data_Images images = { image_star, image_spaceship, image_heart,
		image_shot_ally, image_shot_enemy, image_enemy,
		image_ani_destruction
	};
	return images;
}
/* Free images. */
static void free_images(Data_Images images)
{
	MLV_free_image(images.star);
	MLV_free_image(images.spaceship);
	MLV_free_image(images.heart);
	MLV_free_image(images.shot_ally);
	MLV_free_image(images.shot_enemy);
	MLV_free_image(images.enemy);
	MLV_free_image(images.ani_destruction);
}
/* Load hitbox. */
static Data_Hitbox init_hitbox(const char *path)
{
	char path_hitbox_spaceship[50];
	char path_hitbox_shot_ally[50];
	char path_hitbox_shot_enemy[50];
	char path_hitbox_enemy[50];

	strcpy(path_hitbox_spaceship, path);
	strcat(path_hitbox_spaceship, "src/hitbox/spaceship_hitbox.txt");
	Hitbox hitbox_spaceship = get_hitbox(path_hitbox_spaceship, get_spaceship_width(), get_spaceship_height());

	strcpy(path_hitbox_shot_ally, path);
	strcat(path_hitbox_shot_ally, "src/hitbox/shot_ally_hitbox.txt");
	Hitbox hitbox_shot_ally = get_hitbox(path_hitbox_shot_ally, get_shot_size(), get_shot_size());

	strcpy(path_hitbox_shot_enemy, path);
	strcat(path_hitbox_shot_enemy, "src/hitbox/shot_enemy_hitbox.txt");
	Hitbox hitbox_shot_enemy = get_hitbox(path_hitbox_shot_enemy, get_shot_size(), get_shot_size());

	strcpy(path_hitbox_enemy, path);
	strcat(path_hitbox_enemy, "src/hitbox/enemy_hitbox.txt");
	Hitbox hitbox_enemy = get_hitbox(path_hitbox_enemy, get_enemy_width(), get_enemy_height());

	Data_Hitbox hitbox = { hitbox_spaceship, hitbox_shot_ally, hitbox_shot_enemy, hitbox_enemy };
	return hitbox;
}
/* Free hitbox. */
static void free_hitbox(Data_Hitbox hitbox)
{
	hitbox_free(hitbox.spaceship.rectangle);
	hitbox_free(hitbox.shot_ally.rectangle);
	hitbox_free(hitbox.shot_enemy.rectangle);
	hitbox_free(hitbox.enemy.rectangle);
}
/* Load fonts. */
static Data_Font init_fonts(const char *path)
{
	char path_font_menu_title[50];
	char path_font_menu_choices[50];

	strcpy(path_font_menu_title, path);
	strcat(path_font_menu_title, "src/fonts/Orbitron-Bold.ttf");
	MLV_Font *menu_title = MLV_load_font(path_font_menu_title, 50);

	strcpy(path_font_menu_choices, path);
	strcat(path_font_menu_choices, "src/fonts/Orbitron-Regular.ttf");
	MLV_Font *menu_choices = MLV_load_font(path_font_menu_choices, 25);

	Data_Font fonts = { menu_title, menu_choices };
	return fonts;
}
/* Free fonts. */
static void free_fonts(Data_Font fonts)
{
	MLV_free_font(fonts.menu_title);
	MLV_free_font(fonts.menu_choices);
}
/* Initialize linked lists. */
static Data_List init_lists()
{
	Linked_list stars = linked_list_create();
	Linked_list animations = linked_list_create();
	Linked_list events = linked_list_create();
	Linked_list shots = linked_list_create();
	Linked_list enemies = linked_list_create();

	Data_List lists = { stars, animations, events, shots, enemies };
	return lists;
}
/* Free linked lists. */
static void free_lists(Data_List lists)
{
	linked_list_free(&(lists.animations));
	linked_list_free(&(lists.stars));
	linked_list_free(&(lists.events));
	linked_list_free(&(lists.shots));
	linked_list_free(&(lists.enemies));
}
/* Free animation player. */
static void free_animation_players(Data_List lists)
{
	Element *animation = lists.animations.last;
	while (animation->null == 0)
	{
		MLV_free_animation_player(animation->data.animation.player);
		animation = animation->prev;
	}
}
/* Initialize data for game. */
Data_Game init_data_game(const char *path)
{
	char *path_directory = get_path_data(path);
	Data_Images images = init_images(path_directory);
	Data_Hitbox hitbox = init_hitbox(path_directory);
	Data_Font fonts = init_fonts(path_directory);
	Data_List lists = init_lists();

	Data_Game data = { images, hitbox, fonts, lists };
	return data;
}
/* Free data. */
void free_data(Data_Game data)
{
	free_images(data.images);
	free_hitbox(data.hitbox);
	free_fonts(data.fonts);
	free_animation_players(data.lists);
	free_lists(data.lists);

}