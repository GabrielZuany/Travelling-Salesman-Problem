#include "../headers/tour.h"
#include "../headers/tsp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void dfs(Tour *tour, int *visited, int city, int *numVisitedCities) {
    // Marque a cidade como visitada
    visited[city] = 1;
    tour->tour[*numVisitedCities] = city;
    (*numVisitedCities)++;

    // Verifique todas as cidades adjacentes
    for (Node *node = tour->adjacent_list[city]->head; node != NULL; node = node->next) {
        int adjacentCity = node->value;
        if (!visited[adjacentCity]) {
            dfs(tour, visited, adjacentCity, numVisitedCities);
        }
    }
}

void tour_create(Tour *tour) {
    int numCities = tour->num_cities;
    int *visited = (int*)calloc(numCities, sizeof(int));
    int numVisitedCities = 0;

    // Comece o DFS a partir da cidade 0 (ou qualquer cidade inicial desejada)
    dfs(tour, visited, 0, &numVisitedCities);

    // Certifique-se de que todas as cidades foram visitadas exatamente uma vez
    if (numVisitedCities == numCities) {
        // Se sim, a tour foi criada com sucesso
        free(visited);
        return;
    } else {
        // Caso contrário, algo deu errado
        free(visited);
        // Lide com o erro aqui, se necessário
    }
}

void tour_write_file(Tour *tour, char *path){

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
}