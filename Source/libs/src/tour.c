#include "../headers/tour.h"
#include "../headers/tsp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Tour{
    ForwardList **adjacent_list;
    int *tour;
    int num_cities;
};

int forward_list_comp(const void *a, const void *b){
    
    ForwardList* l1 = *(ForwardList**)a;
    ForwardList* l2 = *(ForwardList**)b;
    unsigned short int city1 = l1->city;
    unsigned short int city2 = l1->city;
    if(city1 > city2){
        return 1;
    }else if(city1 < city2){
        return -1;
    }else{
        return 0;
    }
}

Tour *tour_construct(ForwardList **adjacent_list, int num_cities){

    Tour *tour = (Tour*) malloc(sizeof(Tour));
    
    forward_list_sort(adjacent_list, num_cities, forward_list_comp);

    tour->adjacent_list = adjacent_list;
    tour->tour = (int*) calloc(num_cities,sizeof(int));
    tour->num_cities = num_cities;

    return tour;
}

void tour_destroy(Tour *tour){

    for(int i=0; i < tour->num_cities; i++)
        forward_list_destroy(tour->adjacent_list[i]);

    free(tour->adjacent_list);
    free(tour->tour);
    free(tour);
}

void tour_create(Tour *tour , int start_city) {
    
    bool* visited = (bool*)malloc(tour->num_cities * sizeof(bool));

    for (int i = 0; i < tour->num_cities; i++) {
        visited[i] = false;
    }

    // Pilha para rastrear os nós a serem visitados
    int* stack = (int*)malloc(tour->num_cities * sizeof(int));
    int top = -1;
    int num_cities_visited = 0;

    // Empilhe o nó inicial
    stack[++top] = start_city;

    while (top >= 0) {
        // Desempilhe um nó
        int vertex = stack[top--];

        // Se o nó ainda não foi visitado
        if (!visited[vertex]) {
            tour->tour[num_cities_visited] = vertex;
            num_cities_visited++;
            visited[vertex] = true;
        }

        // Empilhe os nós adjacentes não visitados
        Node* current = tour->adjacent_list[vertex]->head;
        
        while (current != NULL) {
            if (!visited[current->value]) {
                stack[++top] = current->value;
            }
            current = current->next;
        }
    }

    free(visited);
    free(stack);
}

void tour_write_file(Tour *tour){

    char *path = malloc(sizeof(char)*100);
    path = strcpy(path, "Outputs/tour/");
    path = strcat(path, tsp_get_name());
    char *aux = ".tour";
    path = strcat(path, aux);

    FILE *arq = fopen(path,"w");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }
    
    fprintf(arq,"NAME: %s\n", tsp_get_name());
    fprintf(arq,"TYPE: TOUR\n");
    fprintf(arq,"DIMENSION: %hu\n", tour->num_cities);
    fprintf(arq,"TOUR_SECTION\n");


    for(int i=0; i < tour->num_cities; i++)
        fprintf(arq,"%d\n", tour->tour[i]);
    
    fprintf(arq,"EOF");

    fclose(arq);

    free(tsp_get_name());
    free(path);
}