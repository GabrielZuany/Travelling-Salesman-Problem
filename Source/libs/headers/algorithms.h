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

/**
 * @brief Connect all nodes in a graph using a minimum spanning tree algorithm. The algorithm used is Kruskal's algorithm. The algorithm is based on the union_find data structure.
 * 
 * @param n_memb size of the graph
 * @param points graph nodes (coordinates)
 * @param vertex_compare function to compare two vertex objects
 * @param vertex_destroy function to destroy a vertex object
 * @return union_find*
 * 
 * @note Complexity: 
 */
union_find* tsp_build_tree(int n_memb, vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy);


#endif 