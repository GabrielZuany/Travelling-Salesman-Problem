#include "../headers/tour.h"
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
    
    printf("ok\n");
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


int find_next_adjacent(Tour *tour, int *estado, int idx){

    ForwardList **l = tour->adjacent_list;

    Node *aux = l[idx]->head;

    while(aux->next != NULL){

        if(estado[aux->value] == 0){
            estado[aux->value] = 1;
            return aux->value;
        }
        else
            aux = aux->next;
    }
    
    return -1;
}

void tour_creat(Tour *tour){

    ForwardList **adjacent_list = tour->adjacent_list;

    int *estado = (int*) calloc(tour->num_cities, sizeof(int));
    int numCidadesVisitadas = 0;

    tour->tour[numCidadesVisitadas++] = 1;
    estado[0] = 1;
    
    while(numCidadesVisitadas < tour->num_cities){
        
        tour->tour[numCidadesVisitadas++] = find_next_adjacent(adjacent_list, estado, tour->tour[numCidadesVisitadas-1]); 
    }
    
    free(estado);
}

void tour_write_file(Tour *tour, char *path){

    FILE *arq = fopen(path,"w");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char espaco = '\n';

    for(int i=0; i < tour->num_cities; i++){
        fwrite(&tour->tour[i], sizeof(int), 1, arq);
        fwrite(&espaco,sizeof(char),1,arq);
    }

    char *eof = "EOF";
    fwrite(eof, sizeof(char),strlen(eof),arq);

    fclose(arq);
}