#include <stdio.h>
#include "../include/linked_list.h"

int main(int argc, char const *argv[])
{
	Linked_list stars = linked_list_create();

	Data data;
	data.star=star_create(1,1,1,1);
	linked_list_append(&stars,data);
	linked_list_show_star(stars);
	star_move_down(&stars.last->data.star);
	linked_list_show_star(stars);
	linked_list_free(&stars);

	return 0;
}