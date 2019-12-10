#include "../include/data.h"

static Data_Images init_images();
static void free_images(Data_Images);
static Data_Hitbox init_hitbox();
static void free_hitbox(Data_Hitbox);
static Data_Font init_fonts();
static void free_fonts(Data_Font);
static Data_List init_lists();
static void free_lists(Data_List);

static Data_Images init_images()
{
	MLV_Image *image_star = MLV_load_image("src/media/star.png");
	if (!image_star)
	{
		fprintf(stderr, "It was impossible to load the file src/media/star.png.\n");
		exit(1);
	}
	MLV_Image *image_spaceship = MLV_load_image("src/media/spaceship.png");
	if (!image_spaceship)
	{
		fprintf(stderr, "It was impossible to load the file src/media/spaceship.png.\n");
		exit(1);
	}
	MLV_Image *image_heart = MLV_load_image("src/media/heart.png");
	if (!image_heart)
	{
		fprintf(stderr, "It was impossible to load the file src/media/heart.png.\n");
		exit(1);
	}
	MLV_Image *image_shot_ally = MLV_load_image("src/media/shot_ally.png");
	if (!image_shot_ally)
	{
		fprintf(stderr, "It was impossible to load the file src/media/shot_ally.png.\n");
		exit(1);
	}
	MLV_Image *image_shot_enemy = MLV_load_image("src/media/shot_enemy.png");
	if (!image_shot_enemy)
	{
		fprintf(stderr, "It was impossible to load the file src/media/shot_enemy.png.\n");
		exit(1);
	}
	MLV_Image *image_enemy = MLV_load_image("src/media/enemy.png");
	if (!image_enemy)
	{
		fprintf(stderr, "It was impossible to load the file src/media/enemy.png.\n");
		exit(1);
	}
	MLV_Image *image_ani_destruction = MLV_load_image("src/media/destruction.png");
	if (!image_ani_destruction)
	{
		fprintf(stderr, "It was impossible to load the file src/media/destruction.png.\n");
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

static Data_Hitbox init_hitbox()
{
	Hitbox hitbox_spaceship = get_hitbox("src/hitbox/spaceship_hitbox.txt", get_spaceship_width(), get_spaceship_height());
	Hitbox hitbox_shot_ally = get_hitbox("src/hitbox/shot_ally_hitbox.txt", get_shot_size(), get_shot_size());
	Hitbox hitbox_shot_enemy = get_hitbox("src/hitbox/shot_enemy_hitbox.txt", get_shot_size(), get_shot_size());
	Hitbox hitbox_enemy = get_hitbox("src/hitbox/enemy_hitbox.txt", get_enemy_width(), get_enemy_height());

	Data_Hitbox hitbox = { hitbox_spaceship, hitbox_shot_ally, hitbox_shot_enemy, hitbox_enemy };
	return hitbox;
}

static void free_hitbox(Data_Hitbox hitbox)
{
	hitbox_free(hitbox.spaceship.rectangle);
	hitbox_free(hitbox.shot_ally.rectangle);
	hitbox_free(hitbox.shot_enemy.rectangle);
	hitbox_free(hitbox.enemy.rectangle);
}

static Data_Font init_fonts()
{
	MLV_Font *menu_title = MLV_load_font("src/fonts/Orbitron-Bold.ttf", 50);
	MLV_Font *menu_choices = MLV_load_font("src/fonts/Orbitron-Regular.ttf", 25);

	Data_Font fonts = { menu_title, menu_choices };
	return fonts;
}

static void free_fonts(Data_Font fonts)
{
	MLV_free_font(fonts.menu_title);
	MLV_free_font(fonts.menu_choices);
}

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

static void free_lists(Data_List lists)
{
	linked_list_free(&(lists.animations));
	linked_list_free(&(lists.stars));
	linked_list_free(&(lists.events));
	linked_list_free(&(lists.shots));
	linked_list_free(&(lists.enemies));
}

static void free_animation_players(Data_List lists)
{
	Element *animation = lists.animations.last;
	while (animation->null == 0)
	{
		MLV_free_animation_player(animation->data.animation.player);
		animation = animation->prev;
	}
}

Data_Game init_data_game()
{
	Data_Images images = init_images();
	Data_Hitbox hitbox = init_hitbox();
	Data_Font fonts = init_fonts();
	Data_List lists = init_lists();

	Data_Game data = { images, hitbox, fonts, lists };
	return data;
}

void free_data(Data_Game data)
{
	free_images(data.images);
	free_hitbox(data.hitbox);
	free_fonts(data.fonts);
	free_animation_players(data.lists);
	free_lists(data.lists);

}