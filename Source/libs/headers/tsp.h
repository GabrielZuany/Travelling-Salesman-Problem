#ifndef _TSP_
#define _TSP_

#include "../headers/vertex.h"
#include "../headers/edge.h"
#include "../headers/union_find.h"
#include "../headers/utils.h"

#define nan -1
#define TSP_INPUT_FOLDER "/home/zuany/LinuxWorkEnvironmnet/Travelling-Salesman-Problem/Others/exemplos/exemplos/in/"
#define MST_OUTPUT_FOLDER "Outputs/mst/"
#define TOUR_OUTPUT_FOLDER "Outputs/tour/"

// ================== READ AND WRITE =====================//

/**
 * @brief Return the dimension of a tsp file (number of nodes)
 * 
 * @param filepath 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
int tsp_get_dimension();

/**
 * @brief Read a tsp file and return a list of vertexes
 * 
 * @param filepath 
 * @return vertex** 
 * 
 * @note Complexity: 
 */
vertex** tsp_read(char* filepath);

/**
 * @brief Creates a file with the minimum spanning tree of a graph header (bind function)
 * 
 * @param filepath 
 * @param name 
 * @param dimension 
 * @param points 
 * 
 * @note Complexity: 
 */
void _create_mst_file_(char* filepath, char* name, int dimension);


// ============================= CONNECT NODES ================================= //

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


// =============================== BUILD MINIMUN SPANNING TREE =============================//

/**
 * @brief Connect all nodes in a graph using a minimum spanning tree algorithm. The algorithm used is Kruskal's algorithm. The algorithm is based on the union_find data structure.
 * 
 * @param points graph nodes (coordinates)
 * @param vertex_compare function to compare two vertex objects
 * @param vertex_destroy function to destroy a vertex object
 * @return union_find*
 * 
 * @note Complexity: 
 */
union_find* tsp_build_tree(vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy);

#endif