#ifndef _UNION_FIND_
#define _UNION_FIND_

typedef struct tree_node tree_node;
typedef struct union_find union_find;
typedef int (*uf_compare_fn)(void*, void*);
typedef void (*uf_destroy_fn)(void*, ...);

/**
 * @brief Initialize a union find data structure
 * 
 * @param size number of nodes
 * @param compare_fn compare function for nodes
 * @param destroy_fn destroy function for nodes
 * @return union_find* initialized union find data structure
 * 
 * @note Complexity: O(n)
 */
union_find* uf_init(int size, uf_compare_fn compare_fn, uf_destroy_fn destroy_fn);

/**
 * @brief Dealloc memory allocated for union find data structure.
 * 
 * @param uf union find structure.
 * 
 * @note Complexity: O(n) 
 */
void uf_destroy(union_find* uf);

void* uf_find(union_find* uf, void* node);

void uf_union(union_find* uf, void* node1, void* node2);

bool uf_is_connected(union_find* uf, void* node1, void* node2);

#endif