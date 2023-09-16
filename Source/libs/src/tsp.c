#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/vertex.h"
#include "../headers/tsp.h"
#include "../headers/edge.h"
#include "../headers/union_find.h"
#include "../headers/utils.h"

// ============= GET and SET functions =============

int _dimension_(int dimension, char* mode){
    static int _this_dimension_;
    if(strcmp(mode, "get") == 0){
        return _this_dimension_;
    }else if(strcmp(mode, "set") == 0){
        _this_dimension_ = dimension;
    }
}

int tsp_get_dimension(){
    return _dimension_(nan, "get");
}

void tsp_set_dimension(int dimension){
    _dimension_(dimension, "set");
}

char* _name_(char* name, char* mode){
    static char* _this_name_;
    if(strcmp(mode, "get") == 0){
        return _this_name_;
    }else if(strcmp(mode, "set") == 0){
        _this_name_ = name;
    }
}

char* tsp_get_name(){
    return _name_(NULL, "get");
}

void tsp_set_name(char* name){
    _name_(name, "set");
}

char* _filepath_(char* filepath, char* mode){
    static char* _this_filepath_;
    if(strcmp(mode, "get") == 0){
        return _this_filepath_;
    }else if(strcmp(mode, "set") == 0){
        _this_filepath_ = filepath;
    }
}

char* tsp_get_filepath(){
    return _filepath_(NULL, "get");
}

void tsp_set_filepath(char* filepath){
    _filepath_(filepath, "set");
}


// ============= READ and WRITE functions =============

vertex** tsp_read(char* filepath){
    int dimension = 0;
    float x = 0, y = 0;
    char* name = malloc(sizeof(char)*100);
    char line[100];

    FILE* file = fopen(filepath, "r");
    while(fgets(line, 100, file) != NULL){
        if(strstr(line, "NAME")){
            sscanf(line, "NAME : %s", name);
            tsp_set_name(name);
        }else if(strstr(line, "DIMENSION")){
            sscanf(line, "DIMENSION : %d", &dimension);
            tsp_set_dimension(dimension);
        }else if(strstr(line, "NODE_COORD_SECTION")){
            break;
        }
    }

    strcat(name, ".mst");
    _create_mst_file_(MST_OUTPUT_FOLDER, name, dimension);

    vertex** points = malloc(sizeof(vertex*) * dimension);
    int index_garbage = 0;
    for(int i=0; i< dimension; i++){
        fscanf(file, "%d %f %f", &index_garbage, &x, &y);
        points[i] = vertex_init(x, y);
    }

    fclose(file);
    return points;
}

void _create_mst_file_(char* folderpath, char* name, int dimension){
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, folderpath);
    strcat(filepath, name);

    char* type = "MST";
    FILE* file = fopen(filepath, "w");
    fprintf(file, "NAME: %s\nTYPE: %s\nDIMENSION: %d\nMST_SECTION\n", name, type, dimension);    
    fclose(file);
    free(filepath);
}

void _write_in_mst_file_(char* name, int dimension, int idx1, int idx2){
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, MST_OUTPUT_FOLDER);
    strcat(filepath, name);

    FILE* file = fopen(filepath, "a");

    if(idx1 == -1 && idx2 == -1){
        fprintf(file, "EOF");
    }else{
        fprintf(file, "%d %d\n", idx1, idx2);
    }
    fclose(file);
    free(filepath);
}



// ============= BUILD CONNECTIONS =============

int pascal_size(int n_memb){
    int sz = n_memb-1;
    return (sz*(sz+1))/2;
}

int _edge_cmp_(const void* a, const void* b){
    edge* e1 = *(edge**)a;
    edge* e2 = *(edge**)b;
    float d1 = edge_get_distance(e1);
    float d2 = edge_get_distance(e2);
    if(d1 > d2){
        return 1;
    }else if(d1 < d2){
        return -1;
    }else{
        return 0;
    }
}

edge** pascal_connections(vertex** nodes, int n_memb){
    float dist = 0;
    int position = 0;
    int size = pascal_size(n_memb);
    edge** edges = malloc(sizeof(edge*) * size);
    for(int i = 0; i < n_memb; i++){
        for(int j = i + 1; j < n_memb; j++){
            dist = vertex_euclidean_distance(*(nodes + i), *(nodes + j));
            edges[position++] = edge_init(i, j, dist);
        }
    }
    edge_sort(edges, size, _edge_cmp_);
    return edges;
}


// ============= BUILD TREE =============
// Kruskal's algorithm
    // A = vazio
// for cada vertice v pertencente a G.V
    //      MAKE-SET(v)
    // ordene as arestas de G.E em ordem nao decrescente de peso W
    // for cada aresta(u, v) pertencente a G.E, em ordem de peso
    //  if FIND-SET(u) != FIND-SET(v)
    //      A = A U {(u, v)}
    //      UNION(u, v)
    // return A

union_find* tsp_build_tree(vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy){
    int n_memb = tsp_get_dimension();
    union_find* uf = uf_init(n_memb, vertex_compare, vertex_destroy);
    int priority = 0;

    // build the graph (no connections yet)
    for(int i = 0; i<n_memb; i++){
        uf_create_node(uf, points[i], i);
        vertex_set_priority(points[i], i);
        priority++;
    }

    // connect each node to another and sort them by distance
    edge** edge_arr = pascal_connections(points, n_memb);

    // connect the nodes based on lowest distance (kruskal's algorithm)
    int max_edges = n_memb - 1;
    int edges = 0;
    printf("Building MST...\n");
    for(int i = 0; i < pascal_size(n_memb); i++){
        edge* edge1 = edge_arr[i];
        vertex* n1 = points[edge_get_node1_idx(edge1)];
        vertex* n2 = points[edge_get_node2_idx(edge1)];
        tree_node* t1 = uf_find_node(uf, vertex_get_priority(n1));
        tree_node* t2 = uf_find_node(uf, vertex_get_priority(n2));
        if(edges < max_edges && uf_union(uf, t1, t2)){
            _write_in_mst_file_(tsp_get_name(), n_memb, edge_get_node1_idx(edge1) + 1, edge_get_node2_idx(edge1) + 1);
            edges++;
        }
        edge_destroy(edge_arr[i]);
    }
    free(edge_arr);

    _write_in_mst_file_(tsp_get_name(), n_memb, -1, -1);
    free(tsp_get_name());
    return uf;
}
