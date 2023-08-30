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

eucledean_nodes* connected_list(coordinates** points){
    float dist = 0;
    int size = 800;
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

int main(){
    int size = 800;;
    int pascal_size = pascal_arr_size(size);
    printf("PASCAL SIZE: %d\n", pascal_size);
    
    coordinates** points = malloc(sizeof(coordinates*) * size);
    for(int i=0; i<size; i++){
        points[i] = coordinates_init(rand() % 100, rand() % 100);
    }

    eucledean_nodes* eucledean_nodes_arr = connected_list(points);
    free(eucledean_nodes_arr);

    for(int i=0; i<size; i++){ coordinates_destroy(points[i]); }

    free(points);
    return 0;
}