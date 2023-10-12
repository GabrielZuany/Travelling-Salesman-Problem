#ifndef _TOUR_H_
#define _TOUR_H_

#include "forward_list.h"

typedef struct Tour Tour;

/**
 * @brief Init the tour
 * 
 * @return Tour* 
 * 
 * @note Complexity: O(n)
 */
Tour *tour_construct();

/**
 * @brief Dealloc the tour memory.
 * 
 * @param tour 
 * 
 * @note Complexity: O(n)
 */
void tour_destroy(Tour *tour);

/**
 * @brief Run the DFS algorithm to find a valid tour.
 * 
 * @param tour 
 * @param start_city 
 * 
 * @note Complexity: O(V + E) -> O(n)
 */
void tour_run(Tour *tour , int start_city);

/**
 * @brief Write the tour to a file.
 * 
 * @param tour
 * 
 * @note Complexity: O(n) 
 */
void _tour_write_file_(Tour *tour);

#endif