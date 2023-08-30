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
#include "../../Source/libs/headers/coordinates.h"
#include "../../Source/libs/headers/utils.h"

typedef struct eucledean_nodes{
    coordinates* node1;
    coordinates* node2;
    float distance;
}eucledean_nodes;

int pascal_arr_size(int n_memb){
    //T(NE - 1) = (N *(N+1)) / 2
    int sz = n_memb-1;
    return (sz*(sz+1))/2;
}

int compare_euclidean_nodes(const void* a, const void* b){
    eucledean_nodes* a_casted = (eucledean_nodes*) a;
    eucledean_nodes* b_casted = (eucledean_nodes*) b;
    if(a_casted->distance < b_casted->distance)
        return -1;
    else if(a_casted->distance > b_casted->distance)
        return 1;
    return 0;
}

int equal(void* a, void* b){
    eucledean_nodes* a_casted = (eucledean_nodes*) a;
    eucledean_nodes* b_casted = (eucledean_nodes*) b;
    coordinates* a1 = a_casted->node1;
    coordinates* a2 = a_casted->node2;
    float x1 = coordinates_get_x(a1);
    float y1 = coordinates_get_y(a1);
    float x2 = coordinates_get_x(a2);
    float y2 = coordinates_get_y(a2);

    coordinates* b1 = b_casted->node1;
    coordinates* b2 = b_casted->node2;
    float x3 = coordinates_get_x(b1);
    float y3 = coordinates_get_y(b1);
    float x4 = coordinates_get_x(b2);
    float y4 = coordinates_get_y(b2);

    if(x1 == x3 && y1 == y3 && x2 == x4 && y2 == y4)
        return 1;
    return 0;
}

void destroy_euclidean_nodes(void* a, ...){
    eucledean_nodes* a_casted = (eucledean_nodes*) a;
    coordinates_destroy(a_casted->node1);
    coordinates_destroy(a_casted->node2);
    free(a_casted);
}

eucledean_nodes* connected_list(coordinates** points){
    float dist = 0;
    int size = 5;
    int writed = 0;
    int pascal_size = pascal_arr_size(size);
    int eucl_writed = 0;

    eucledean_nodes* eucledean_nodes_arr = malloc(sizeof(eucledean_nodes) * pascal_size);

    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            dist = coordinates_euclidean_distance(points[i], points[j]);
            eucledean_nodes_arr[eucl_writed].node1 = points[i];
            eucledean_nodes_arr[eucl_writed].node2 = points[j];
            eucledean_nodes_arr[eucl_writed].distance = dist;
            eucl_writed++;
        }
    }
    qsort(eucledean_nodes_arr, pascal_size, sizeof(eucledean_nodes), compare_euclidean_nodes);
    return eucledean_nodes_arr;
}

void print_coordinates(coordinates* c){
    printf("(%.2f, %.2f)", coordinates_get_x(c), coordinates_get_y(c));
}

int main(){
    int size = 5;
    int pascal_size = pascal_arr_size(size);
    printf("PASCAL SIZE: %d\n", pascal_size);
    
    coordinates** points = malloc(sizeof(coordinates*) * size);
    for(int i=0; i<size; i++){
        points[i] = coordinates_init(rand() % 100, rand() % 100);
        printf("POINT %d: (%.2f, %.2f)\n", i, coordinates_get_x(points[i]), coordinates_get_y(points[i]));
    }

    eucledean_nodes* eucledean_nodes_arr = connected_list(points);

    union_find* uf = uf_init(size, equal, destroy_euclidean_nodes);
    tree_node* t1 = NULL;
    tree_node* t2 = NULL;
    int priority = 0;
    for(int i=0; i<pascal_size; i++){
        eucledean_nodes* node = &eucledean_nodes_arr[i];
        coordinates* node1 = node->node1;
        coordinates* node2 = node->node2;
        t1 = uf_create_node(uf, node1, priority++);
        t2 = uf_create_node(uf, node2, priority);
        if(!uf_is_connected(uf, t1, t2)){
            uf_union(uf, t1, t2);
            //printf("NODE1: (%f, %f) NODE2: (%f, %f) DISTANCE: %f\n", coordinates_get_x(node1), coordinates_get_y(node1), coordinates_get_x(node2), coordinates_get_y(node2), node->distance);
        }
    }

    _d_uf_print_(uf);    
    for(int i=0; i<size; i++){
        tree_node* tn = uf_find_node(uf, i);
        _d_print_node_(tn, print_coordinates);
        printf("\n");
    }

    free(eucledean_nodes_arr);

    for(int i=0; i<size; i++){ coordinates_destroy(points[i]); }

    free(points);
    return 0;
}