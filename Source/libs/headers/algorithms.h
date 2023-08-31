#ifndef _ALGORITHMS_
#define _ALGORITHMS_
#include "edge.h"
#include "vertex.h"
#include "union_find.h"

/**
 * @brief Build the a list of connected nodes with their respective distances using an algorithm that takes a lot of memory (size follows the pascal triangle logic). Connects one node with each graph node. Then sorts it using quick sort and distance as comparative parameter. Size: 1 -> 3 -> 6 -> 10 -> 15 -> 21 -> 28 -> ...
 * 
 * @param nodes graph nodes
 * @param n_memb number of graph nodes
 * @return edge** 
 * 
 * @note Complexity 
 * @note Array size: T(n_memb - 1) = (N *(N+1)) / 2
 */
edge** pascal_connections(vertex** nodes, int n_memb);

/**
 * @brief Return the size of edge array based on pascal_connections algorithm
 * 
 * @param n_memb 
 * @return int 
 */
int pascal_size(int n_memb);




union_find* tsp_build_tree(int n_memb);


#endif 