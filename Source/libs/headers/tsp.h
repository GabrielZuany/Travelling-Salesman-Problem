#ifndef _TSP_
#define _TSP_

#include "../headers/vertex.h"
#include "../headers/union_find.h"
#include "../headers/utils.h"
#include "../headers/forward_list.h"

#define nan -1
typedef char opcode;
#define get 'g'
#define set 's'
#define limit 65535

#define MST_OUTPUT_FOLDER "Outputs/mst/"
#define TOUR_OUTPUT_FOLDER "Outputs/tour/"
#define PROFILER_OUTPUT_PATH "Profiler/srcprof.csv"

typedef struct edge edge;

// ==================== PROFILE ====================
/**
 * @brief Initialize the profiling
 * 
 * @note Complexity: O(1)
 */
void profile_init();

/**
 * @brief Finish the profiling and write the results in a csv file
 * 
 * @note Complexity: O(1)
 */
void end_profile();


// ================== READ AND WRITE =====================//
/**
 * @brief Return the dimension of a tsp file (number of nodes)
 * 
 * @param filepath 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
unsigned short int tsp_get_dimension();

/**
 * @brief Read a tsp file and return a list of vertexes
 * 
 * @param filepath 
 * @return vertex** 
 * 
 * @note Complexity: O(n)
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
 * @note Complexity: O(1)
 */
void _create_mst_file_(char* filepath, char* name, unsigned short int dimension);


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
 * 
 * @note Complexity: O(n^2)
 */
edge* all_possible_edges(vertex** nodes, unsigned short int n_memb);

/**
 * @brief Return the size of edge array based on all_possible_edges algorithm
 * 
 * @param n_memb 
 * @return int 
 * 
 * @note Complexity: O(1)
 */
unsigned int all_possible_edges_length(unsigned short int n_memb);


// =============================== STATIC DATA IN MEMORY ================================= //
/**
 * @brief Returns a list of lists in which each list represents the adjacency list of a vertex
 * 
 * @return ForwardList** 
 * 
 * @note Complexity: O(1)
 */
ForwardList** _get_adjacency_list_();

/**
 * @brief Returns the name of tsp file
 * 
 * @return char* 
 * 
 * @note Complexity: O(1)
 */
char* tsp_get_name();


// =============================== BUILD MINIMUN SPANNING TREE ============================= //
/**
 * @brief Connect all nodes in a graph using a minimum spanning tree algorithm. The algorithm used is Kruskal's algorithm. The algorithm is based on the union_find data structure.
 * 
 * @param points graph nodes (coordinates)
 * @param vertex_compare function to compare two vertex objects
 * @param vertex_destroy function to destroy a vertex object
 * @return union_find*
 * 
 * @note Complexity: O(n^2) 
 */
union_find* tsp_build_tree(vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy);

#endif