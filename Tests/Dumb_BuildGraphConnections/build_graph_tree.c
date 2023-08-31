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
#include "../../Source/libs/headers/graph_node.h"
#include "../../Source/libs/headers/utils.h"

typedef struct eucledean_nodes{
    graph_node* node1;
    graph_node* node2;
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
    graph_node* a_casted = (graph_node*) a;
    graph_node* b_casted = (graph_node*) b;
    if(graph_node_get_x(a_casted) == graph_node_get_x(b_casted) && graph_node_get_y(a_casted) == graph_node_get_y(b_casted))
        return 1;
    return 0;
}

void destroy_euclidean_nodes(void* a, ...){
    eucledean_nodes* a_casted = (eucledean_nodes*) a;
    graph_node_destroy(a_casted->node1);
    graph_node_destroy(a_casted->node2);
    free(a_casted);
}

eucledean_nodes* connected_list(graph_node** points){
    float dist = 0;
    int size = 5;
    int writed = 0;
    int pascal_size = pascal_arr_size(size);
    int eucl_writed = 0;

    eucledean_nodes* eucledean_nodes_arr = malloc(sizeof(eucledean_nodes) * pascal_size);

    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            dist = graph_node_euclidean_distance(points[i], points[j]);
            eucledean_nodes_arr[eucl_writed].node1 = points[i];
            eucledean_nodes_arr[eucl_writed].node2 = points[j];
            eucledean_nodes_arr[eucl_writed].distance = dist;
            eucl_writed++;
        }
    }
    qsort(eucledean_nodes_arr, pascal_size, sizeof(eucledean_nodes), compare_euclidean_nodes);

    for(int i=0; i<pascal_size; i++){
        printf("NODE1: (%.2f, %.2f) NODE2: (%.2f, %.2f) DISTANCE: %.2f\n", graph_node_get_x(eucledean_nodes_arr[i].node1), graph_node_get_y(eucledean_nodes_arr[i].node1), graph_node_get_x(eucledean_nodes_arr[i].node2), graph_node_get_y(eucledean_nodes_arr[i].node2), eucledean_nodes_arr[i].distance);
    }
    printf("\n");
    return eucledean_nodes_arr;
}

void print_graph_node(graph_node* c){
    printf("(%.2f, %.2f)", graph_node_get_x(c), graph_node_get_y(c));
}

int main(){
    int size = 5;
    int pascal_size = pascal_arr_size(size);
    printf("PASCAL SIZE: %d\n", pascal_size);
    
    int priority = 0;
    union_find* uf = uf_init(size, graph_node_compare, graph_node_destroy);
    graph_node** points = malloc(sizeof(graph_node*) * size);
    for(int i=0; i<size; i++){
        points[i] = graph_node_init(rand() % 10, rand() % 10);
        //printf("POINT %d: (%.2f, %.2f)\n", i, graph_node_get_x(points[i]), graph_node_get_y(points[i]));
        uf_create_node(uf, points[i], priority);
        graph_node_set_priority(points[i], priority);
        priority++;
    }

    eucledean_nodes* eucledean_nodes_arr = connected_list(points);

    tree_node* t1 = NULL;
    tree_node* t2 = NULL;
    priority = 0;
    for(int i=0; i<pascal_size; i++){
        eucledean_nodes* node = &eucledean_nodes_arr[i];
        graph_node* node1 = node->node1;
        graph_node* node2 = node->node2;
        t1 = uf_find_node(uf, graph_node_get_priority(node1));
        t2 = uf_find_node(uf, graph_node_get_priority(node2));
        
        if(!uf_is_connected(uf, t1, t2)){
            uf_union(uf, t1, t2);  
            printf("NODE1[%d]: (%.2f, %.2f) NODE2[%d]: (%.2f, %.2f) DISTANCE: %.2f\n", graph_node_get_priority(node1), graph_node_get_x(node1), graph_node_get_y(node1), graph_node_get_priority(node2), graph_node_get_x(node2), graph_node_get_y(node2), node->distance);

            _d_uf_print_(uf);
            printf("\n---\n");
        }
    }

    _d_uf_print_(uf);    
    for(int i=0; i<size; i++){
        tree_node* tn = uf_find_node(uf, i);
        _d_print_node_(tn, print_graph_node);
        printf("\n");
    }

    free(eucledean_nodes_arr);
    for(int i=0; i<size; i++){ graph_node_destroy(points[i]); }
    free(points);
    return 0;
}