#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/vertex.h"
#include "../headers/tsp.h"
#include "../headers/edge.h"
#include "../headers/union_find.h"
#include "../headers/connection.h"
#include "../headers/utils.h"

int _dimension_(int dimension, char* mode){
    static int _this_dimension_;
    if(strcmp(mode, "get")){
        return _this_dimension_;
    }else if(strcmp(mode, "set")){
        _this_dimension_ = dimension;
    }
}

vertex** read_tsp(char* filepath){
    //vertex** points = NULL;
    FILE* file = fopen(filepath, "r");

    int dimension = 100; // from file
    _dimension_(dimension, "set");
    float x = 0, y = 0; // from file
    char name[] = ""; // from file

    //_write_mst_(MST_OUTPUT_FOLDER, name, dimension, NULL);
    //_write_tour_(TOUR_OUTPUT_FOLDER, name, dimension, NULL);

    vertex** points = malloc(sizeof(vertex*) * dimension);
    for(int i=0; i< dimension; i++){
        points[i] = vertex_init(rand() % 10, rand() % 10);
    }

    fclose(file);
    return points;
}

void _write_mst_(char* filepath, char* name, int dimension, vertex** points){
    // if open for the first time
    if(points == NULL){
        char type[] = "MST";
        FILE* file = fopen(filepath, "w");
        // write: name, dimension, MST
        fclose(file);
        return;
    }

    FILE* file = fopen(filepath, "a");


    //write EOF at end of file
    fclose(file);
}

void _write_tour_(char* filepath, char* name, int dimension, vertex** points, int* tour){
    // tour => array of points indexes (avoid create a vertex** copy)

    // if open for the first time
    if(points == NULL){
        char type[] = "TOUR";
        FILE* file = fopen(filepath, "w");
        // write: name, dimension, MST
        fclose(file);
        return;
    }
    
    FILE* file = fopen(filepath, "a");


    //write EOF at end of file
    fclose(file);
}


union_find* tsp_build_tree(int n_memb, vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy){
    //n_memb = _dimension_(nan, "get");
    union_find* uf = uf_init(n_memb, vertex_compare, vertex_destroy);
    int priority = 0;

    // build the graph (no connections yet)
    for(int i = 0; i<n_memb; i++){
        uf_create_node(uf, points[i], i);
        vertex_set_priority(points[i], i);
        priority++;
    }

    // connect each node to another and sort them by distance
    edge** edge_arr = pascal_connections(points, n_memb);

    // connect the nodes based on lowest distance (kruskal's algorithm)
    for(int i = 0; i < pascal_size(n_memb); i++){
        edge* edge1 = edge_arr[i];
        vertex* n1 = points[edge_get_node1_idx(edge1)];
        vertex* n2 = points[edge_get_node2_idx(edge1)];
        tree_node* t1 = uf_find_node(uf, vertex_get_priority(n1));
        tree_node* t2 = uf_find_node(uf, vertex_get_priority(n2));
        uf_union(uf, t1, t2);
        // i can append in mst file in case of union sucess []
        // avoid on loop of size N                          []
        // change uf_union return                           []
    }
    
    // free the edges
    for(int i = 0; i < pascal_size(n_memb); i++){
        edge_destroy(edge_arr[i]);
    }
    free(edge_arr);
    
    return uf;
}
