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
    return 0;
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
    return NULL;
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
    return NULL;
}

char* tsp_get_filepath(){
    return _filepath_(NULL, "get");
}

void tsp_set_filepath(char* filepath){
    _filepath_(filepath, "set");
}


// ==================== TOUR ===================

typedef int tour;

int _exists_in_tour_(int* tour, int id){
    for(int i = 0; i < tsp_get_dimension(); i++){
        if(tour[i] == id){
            return 1;
        }
    }
    return 0;
}

FILE* _open_tour_(){
    char* name = tsp_get_name();
    char* folderpath = TOUR_OUTPUT_FOLDER;
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, folderpath);
    strcat(filepath, name);
    strcat(filepath, ".tour");

    FILE* file = fopen(filepath, "w");
    free(filepath);
    return file;
}

void _close_tour_(FILE* tour_file){
    fprintf(tour_file, "EOF");
    fclose(tour_file);
}

void _write_tour_header(FILE* tour_file){
    char* name = tsp_get_name();
    char* type = "TOUR";
    int dimension = tsp_get_dimension();
    fprintf(tour_file, "NAME: %s\nTYPE: %s\nDIMENSION: %d\nTOUR_SECTION\n", name, type, dimension);    
}

void _tour_write_vertex_idx_(FILE* tour_file, int vertex_idx){
    fprintf(tour_file, "%d\n", vertex_idx);
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
    strcat(filepath, ".mst");

    char* type = "MST";
    FILE* file = fopen(filepath, "w");
    fprintf(file, "NAME: %s\nTYPE: %s\nDIMENSION: %d\nMST_SECTION\n", name, type, dimension);    
    fclose(file);
    free(filepath);
}

void _write_in_mst_file_(char* name, int idx1, int idx2){
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, MST_OUTPUT_FOLDER);
    strcat(filepath, name);
    strcat(filepath, ".mst");

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


// ============= MINIMUM SPANNING TREE =============

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

    // init tour file
    FILE* tour_file = _open_tour_();
    _write_tour_header(tour_file);
    tour* tour = calloc(sizeof(tour), n_memb);
    int tour_idx = 0;
    
    // build mst and tour both together
    for(int i = 0; i < pascal_size(n_memb); i++){
        if(edges < max_edges){
            edge* current_edge = edge_arr[i];
            int vertex1_idx = edge_get_node1_idx(current_edge);
            int vertex2_idx = edge_get_node2_idx(current_edge);
            vertex* vertex1 = points[vertex1_idx];
            vertex* vertex2 = points[vertex2_idx];
            tree_node* tree_node1 = uf_find_node(uf, vertex_get_priority(vertex1));
            tree_node* tree_node2 = uf_find_node(uf, vertex_get_priority(vertex2));

            if(uf_union(uf, tree_node1, tree_node2)){
                _write_in_mst_file_(tsp_get_name(), vertex1_idx + 1, vertex2_idx + 1);
                edges++;
                if(!_exists_in_tour_(tour, vertex1_idx + 1)){
                    tour[tour_idx++] = vertex1_idx + 1;
                    _tour_write_vertex_idx_(tour_file, vertex1_idx + 1);
                }
                if(!_exists_in_tour_(tour, vertex2_idx + 1)){
                    tour[tour_idx++] = vertex2_idx + 1;
                    _tour_write_vertex_idx_(tour_file, vertex2_idx + 1);
                }
            }
        }
        edge_destroy(edge_arr[i]);
    }
    
    _write_in_mst_file_(tsp_get_name(), -1, -1);
    _close_tour_(tour_file);
    free(edge_arr);
    free(tsp_get_name());
    free(tour);
    return uf;
}
