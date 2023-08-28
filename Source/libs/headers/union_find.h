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

/**
 * @brief Retrieves the data stored into tree_node datatype 
 * 
 * @param uf 
 * @param priority 
 * @return tree_node* 
 * 
 * @note Complexity: O(log(n))
 */
void* uf_find_data(union_find* uf, tree_node* node);

/**
 * @brief Retrieves the node based in given priority value;
 * 
 * @param uf 
 * @param priority 
 * @return tree_node* 
 *  
 *  @note Complexity: O(1)
 */
tree_node* uf_find_node(union_find* uf, int priority);

/**
 * @brief Join 2 nodes using weighted quick sort
 * 
 * @param uf 
 * @param node1 
 * @param node2 
 * 
 * @note Complexity: O(log(n))
 */
void uf_union(union_find* uf, tree_node* node1, tree_node* node2);

/**
 * @brief 
 * 
 * @param uf 
 * @param node1 
 * @param node2 
 * @return int 
 * 
 * @note Complexity: O(log(n))
 */
int uf_is_connected(union_find* uf, tree_node* node1, tree_node* node2);

/**
 * @brief Assigns a void* data value into a node previously allocacted
 * 
 * @param uf 
 * @param new_node void* generic value
 * @param priority priority (array position) in 'tree'.
 * @return tree_node* 
 * 
 * @note Complexity: O(1)
 */
tree_node* uf_create_node(union_find* uf, void* new_node, int priority);

#ifdef _DEV_
    /**
     * @brief Prints the union find data structure (for debug/test purposes -> compile with $ args -D _DEV_)
     * 
     * @note Bind function
     * 
     * @param uf 
     * 
     * @note Complexity: O(n)
     */
    void _d_uf_print_(union_find* uf);

    /**
     * @brief Fills the union find data structure with integers (for debug/test purposes -> compile with $ args -D _DEV_)
     * 
     * @note Bind function
     * 
     * @param uf 
     * 
     * @note Complexity: O(n)
     */
    tree_node** _d_uf_fill_int_(union_find* uf);
#endif

#endif