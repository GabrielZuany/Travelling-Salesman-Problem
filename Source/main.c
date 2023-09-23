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
    
    //argv[1] = "Others/exemplos/exemplos/in/berlin52.tsp";
    vertex** points = tsp_read(argv[1]);
    union_find* uf = tsp_build_tree(points, vertex_compare, vertex_destroy_wrapper);

    Tour *tour = tour_construct(_get_adjacency_list_(), tsp_get_dimension());

    tour_create(tour, 0);

    tour_write_file(tour);
    
    
    tour_destroy(tour);
    uf_destroy(uf);
    free(points);
    return 0;
}