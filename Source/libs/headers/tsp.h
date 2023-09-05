#ifndef _TSP_
#define _TSP_

#include "../headers/vertex.h"
#include "../headers/edge.h"
#include "../headers/union_find.h"
#include "../headers/utils.h"

#define nan -1
#define MST_OUTPUT_FOLDER "not defined"
#define TOUR_OUTPUT_FOLDER "not defined"

/**
 * @brief 
 * 
 * @param filepath 
 * @return vertex** 
 */
vertex** read_tsp(char* filepath);

/**
 * @brief 
 * 
 * @param filepath 
 * @param name 
 * @param dimension 
 * @param points 
 */
void _write_mst_(char* filepath, char* name, int dimension, vertex** points);

/**
 * @brief 
 * 
 * @param filepath 
 * @param name 
 * @param dimension 
 * @param points 
 * @param tour 
 */
void _write_tour_(char* filepath, char* name, int dimension, vertex** points, int* tour);


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