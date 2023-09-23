#ifndef _TOUR_H_
#define _TOUR_H_

#include "forward_list.h"

typedef struct Tour Tour;

Tour *tour_construct(ForwardList **adjacent_list, int num_cities);

void tour_destroy(Tour *tour);

int find_next_adjacent(Tour *tour, int *estado, int idx);

void tour_create(Tour *tour , int start_city);

void tour_write_file(Tour *tour);

#endif