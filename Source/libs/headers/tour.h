#ifndef _TOUR_H_
#define _TOUR_H_

#include "forward_list.h"

typedef struct Tour Tour;

/**
 * @brief Cria uma estrutura do Tour
 * 
 * @param adjacent_list lista de vertices adjacentes para aplicar o DFS
 * @param num_cities 
 * @return Tour* 
 */
Tour *tour_construct(ForwardList **adjacent_list, int num_cities);

/**
 * @brief Libera a memoria alocada pelo tour
 * 
 * @param tour 
 */
void tour_destroy(Tour *tour);

/**
 * @brief Aplica o DFS recursivamente para criar o tour
 * 
 * @param tour 
 * @param start_city 
 */
void tour_create(Tour *tour , int start_city);

/**
 * @brief Escreve o arquivo do tour
 * 
 * @param tour 
 */
void tour_write_file(Tour *tour);

#endif