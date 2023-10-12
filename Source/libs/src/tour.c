#include "../headers/tour.h"
#include "../headers/tsp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct Tour{
    ForwardList **adjacent_list;
    int *tour;
    int num_cities;
};

Tour *tour_construct(){
    int size = tsp_get_dimension();
    Tour *tour = (Tour*) malloc(sizeof(Tour));
    tour->adjacent_list = _get_adjacency_list_();
    tour->tour = (int*) calloc(size, sizeof(int));
    tour->num_cities = size;

    return tour;
}

void tour_destroy(Tour *tour){
    for(int i=0; i < tour->num_cities; i++){
        forward_list_destroy(tour->adjacent_list[i]);
    }
    free(tour->adjacent_list);
    free(tour->tour);
    free(tour);
}

void tour_run(Tour *tour , int start_city) {
    clock_t clk = clock();
    bool* visited = (bool*)malloc(tour->num_cities * sizeof(bool));
    for (int i = 0; i < tour->num_cities; i++) {
        visited[i] = false;
    }

    int* stack = (int*)malloc(tour->num_cities * sizeof(int));
    int top = -1;
    int num_cities_visited = 0;

    stack[++top] = start_city;

    while (top >= 0) {
        
        int vertex = stack[top--];

        if (!visited[vertex]) {
            tour->tour[num_cities_visited] = vertex;
            num_cities_visited++;
            visited[vertex] = true;
        }

        Node* current = tour->adjacent_list[vertex]->head;
        
        while (current != NULL) {
            if (!visited[current->value]) {
                stack[++top] = current->value;
            }
            current = current->next;
        }
    }
    _end_clk_(clk);
    _tour_write_file_(tour);
    free(visited);
    free(stack);
}

void _tour_write_file_(Tour *tour){
    char *path = malloc(sizeof(char)*100);
    path = strcpy(path, "Outputs/tour/");
    path = strcat(path, tsp_get_name());
    char *aux = ".tour";
    path = strcat(path, aux);

    FILE *arq = fopen(path,"w");

    if(arq == NULL){
        printf("Error opening file! You must have 'Outputs/tour/' folder!\n");
        exit(1);
    }
    
    fprintf(arq,"NAME: %s\n", tsp_get_name());
    fprintf(arq,"TYPE: TOUR\n");
    fprintf(arq,"DIMENSION: %hu\n", tour->num_cities);
    fprintf(arq,"TOUR_SECTION\n");


    for(int i=0; i < tour->num_cities; i++)
        fprintf(arq,"%d\n", (tour->tour[i])+1);
    
    fprintf(arq,"EOF");

    fclose(arq);
    free(tsp_get_name());
    free(path);
}