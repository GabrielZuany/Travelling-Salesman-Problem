/**
 * @brief PASCAL TRIANGLE ARRAY SIZE
 * 
 * @note T(NE - 1) = (N *(N+1)) / 2
 * @note CAN BE VERY SLOW
 * @note USES A LOT OF MEMORY
 * 
 * @note ONE OF THE WORST WAYS TO DO THIS
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Source/libs/headers/union_find.h"
#include "../../Source/libs/headers/vertex.h"
#include "../../Source/libs/headers/utils.h"
#include "../../Source/libs/headers/edge.h"
#include "../../Source/libs/headers/algorithms.h"

void print_vertex(vertex* c){
    printf("(%.2f, %.2f)", vertex_get_x(c), vertex_get_y(c));
}

int main(){
    int size = 1000;  

    vertex** points = malloc(sizeof(vertex*) * size);
    for(int i=0; i<size; i++){
        points[i] = vertex_init(rand() % 10, rand() % 10);
    }

    union_find* uf = tsp_build_tree(size, points, vertex_compare, vertex_destroy); // fix this

    _d_uf_print_(uf);    
    for(int i=0; i<size; i++){
        tree_node* tn = uf_find_node(uf, i);
        _d_print_node_(tn, print_vertex);
        printf("\n");
    }

    uf_destroy(uf);
    free(points);
    return 0;
}