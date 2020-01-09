#ifndef STARS_H_INCLUDED
#define STARS_H_INCLUDED

void stars_show(const Linked_list stars);

void stars_move_down(Linked_list *stars, const int window_height);

void stars_create_star(Linked_list *stars, const int window_width);

#endif 