#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libs/headers/union_find.h"
#include "libs/headers/vertex.h"
#include "libs/headers/utils.h"
#include "libs/headers/tsp.h"
#include "libs/headers/forward_list.h"
#include "libs/headers/tour.h"

int main(int argc, char** argv){
    profile_init();
    vertex** points = tsp_read(argv[1]);
    union_find* uf = tsp_build_tree(points, vertex_compare, vertex_destroy_wrapper);
    Tour *tour = tour_construct();

    tour_run(tour, 0);
    tour_destroy(tour);

    uf_destroy(uf);
    free(points);
    
    end_profile();
    return 0;
}