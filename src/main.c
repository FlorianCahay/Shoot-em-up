#include <stdio.h>
#include "../include/linked_list.h"

int main(int argc, char const *argv[])
{
	Linked_list stars = linked_list_create();

	Data data;
	data.i=4;
	linked_list_append(&stars,data);

	data.i=7;
	linked_list_append(&stars,data);

	data.i=8;
	linked_list_append(&stars,data);
	
	linked_list_remove(stars.last);
	linked_list_show_int(stars);
	linked_list_free(&stars);

	return 0;
}