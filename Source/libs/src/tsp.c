#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/vertex.h"
#include "../headers/tsp.h"
#include "../headers/edge.h"
#include "../headers/union_find.h"
#include "../headers/utils.h"
#include "../headers/forward_list.h"
#include <time.h>

// ==================== PROFILE ====================

void __prof_set_header__(FILE* out){
    fprintf(out, "N_MEMB;READ_TSP;BUILD_ALL_EDGES;BUILD_MST;BUILD_TOUR;\n");
}

void _profile_(float data){
    FILE* prof = fopen(PROFILER_OUTPUT_PATH, "a");
    if(prof == NULL){
        prof = fopen(PROFILER_OUTPUT_PATH, "w");
        __prof_set_header__(prof);
    }
    fprintf(prof, "%f;", data);
    fclose(prof);
}

void _end_clk_(clock_t t){
    t = clock() - t;
    float time_taken = ((float)t)/CLOCKS_PER_SEC;
    _profile_(time_taken);
}

void _end_profile_(){
    FILE* prof = fopen(PROFILER_OUTPUT_PATH, "a");
    fputc('\n', prof);
    fclose(prof);
}


// ============= GET and SET functions =============

unsigned short int _dimension_(unsigned short int dimension, opcode mode){
    static unsigned short int _this_dimension_;
    if(mode == get){
        return _this_dimension_;
    }else if(mode == set){
        _this_dimension_ = dimension;
    }
}

unsigned short int tsp_get_dimension(){
    return _dimension_(nan, get);
}

void tsp_set_dimension(unsigned short int dimension){
    _dimension_(dimension, set);
}

char* _name_(char* name, opcode mode){
    static char* _this_name_;
    if(mode == get){
        return _this_name_;
    }else if(mode == set){
        _this_name_ = name;
    }
}

char* tsp_get_name(){
    return _name_(NULL, get);
}

void tsp_set_name(char* name){
    _name_(name, set);
}

char* _filepath_(char* filepath, opcode mode){
    static char* _this_filepath_;
    if(mode == get){
        return _this_filepath_;
    }else if(mode == set){
        _this_filepath_ = filepath;
    }
}

char* tsp_get_filepath(){
    return _filepath_(NULL, get);
}

void tsp_set_filepath(char* filepath){
    _filepath_(filepath, set);
}


// ==================== TOUR ===================

typedef unsigned short int tour;

// need to optimize
boolean _exists_in_tour_(unsigned short int* tour, unsigned short int id){
    unsigned short int dimension = tsp_get_dimension();
    for(unsigned short int i = 0; i < dimension; i++){
        if(tour[i] == id){
            return True;
        }
    }
    return False;
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
    unsigned short int dimension = tsp_get_dimension();
    fprintf(tour_file, "NAME: %s\nTYPE: %s\nDIMENSION: %hu\nTOUR_SECTION\n", name, type, dimension);    
}

void _tour_write_vertex_idx_(FILE* tour_file, unsigned short int vertex_idx){
    fprintf(tour_file, "%hu\n", vertex_idx);
}


// ============= READ and WRITE functions =============

vertex** tsp_read(char* filepath){
    unsigned short int dimension = 0;
    float x = 0, y = 0;
    char* name = malloc(sizeof(char)*100);
    char line[100];

    FILE* file = fopen(filepath, "r");
    clock_t t = clock();
    while(fgets(line, 100, file) != NULL){
        if(strstr(line, "NAME")){
            sscanf(line, "NAME : %s", name);
            tsp_set_name(name);
        }else if(strstr(line, "DIMENSION")){
            sscanf(line, "DIMENSION : %hu", &dimension);
            tsp_set_dimension(dimension);
        }else if(strstr(line, "NODE_COORD_SECTION")){
            break;
        }
    }
    
    _create_mst_file_(MST_OUTPUT_FOLDER, name, dimension);

    vertex** points = malloc(sizeof(vertex*) * dimension);
    unsigned short int index_garbage = 0;
    for(unsigned short int i=0; i< dimension; i++){
        fscanf(file, "%hu %f %f", &index_garbage, &x, &y);
        points[i] = vertex_init(x, y);
    }

    _profile_(dimension);
    _end_clk_(t);

    fclose(file);
    return points;
}

void _create_mst_file_(char* folderpath, char* name, unsigned short int dimension){
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, folderpath);
    strcat(filepath, name);
    strcat(filepath, ".mst");

    char* type = "MST";
    FILE* file = fopen(filepath, "w");
    fprintf(file, "NAME: %s\nTYPE: %s\nDIMENSION: %hu\nMST_SECTION\n", name, type, dimension);    
    fclose(file);
    free(filepath);
}

void _write_in_mst_file_(char* name, unsigned short int idx1, unsigned short int idx2){
    char* filepath = malloc(sizeof(char) * 1000);
    strcpy(filepath, MST_OUTPUT_FOLDER);
    strcat(filepath, name);
    strcat(filepath, ".mst");

    FILE* file = fopen(filepath, "a");

    if(idx1 == limit && idx2 == limit){
        fprintf(file, "EOF");
    }else{
        fprintf(file, "%hu %hu\n", idx1, idx2);
    }
    fclose(file);
    free(filepath);
}

// ============= BUILD CONNECTIONS =============

unsigned int pascal_size(unsigned short int n_memb){
    return ((n_memb-1)*((n_memb-1)+1))/2;
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

edge** pascal_connections(vertex** nodes, unsigned short int n_memb){
    float dist = 0;
    unsigned int position = 0;
    unsigned int size = pascal_size(n_memb);
    edge** edges = malloc(sizeof(edge*) * size);
    clock_t t = clock();

    for(unsigned short int i = 0; i < n_memb; i++){
        for(unsigned short int j = i + 1; j < n_memb; j++){
            dist = vertex_euclidean_distance(*(nodes + i), *(nodes + j));
            edges[position++] = edge_init(i, j, dist);
        }
    }

    _end_clk_(t);

    t = clock();
    edge_sort(edges, size, _edge_cmp_);
    _end_clk_(t);

    return edges;
}


// ============= MINIMUM SPANNING TREE =============

ForwardList** _adjacency_list_(opcode mode, ForwardList** adjacency_list){
    static ForwardList** _this_adjacency_list_;
    if(mode == get){
        return _this_adjacency_list_;
    }else if(mode == set){
        _this_adjacency_list_ = adjacency_list;
    }
}

ForwardList** _get_adjacency_list_(){
    return _adjacency_list_(get, NULL);
}

void _set_adjacency_list_(ForwardList** adjacency_list){
    _adjacency_list_(set, adjacency_list);
}

void _adjacency_list_destroy_(unsigned short int n_memb){
    ForwardList** arr_adjacency_lists = _get_adjacency_list_();
    for(unsigned short int i = 0; i < n_memb; i++){
        forward_list_destroy(arr_adjacency_lists[i]);
    }
    free(arr_adjacency_lists);
}

void print_int(int i){
    printf("%d ", i);
}


void _set_graph_vertices_(union_find* uf, vertex** points, unsigned short int n_memb){
    unsigned short int priority = 0;
    for(unsigned short int i = 0; i<n_memb; i++){
        uf_create_node(uf, points[i], i);
        vertex_set_priority(points[i], i);
        priority++;
    }
}

union_find* tsp_build_tree(vertex** points, compare_fn vertex_compare, destroy_fn vertex_destroy){
    unsigned short int n_memb = tsp_get_dimension();
    union_find* uf = uf_init(n_memb, vertex_compare, vertex_destroy);

    // each position contains a forward list that represents the adjacency list of the vertex
    ForwardList** arr_adjacency_lists = malloc(sizeof(ForwardList*) * n_memb);
    for(unsigned short int i = 0; i < n_memb; i++){
        arr_adjacency_lists[i] = forward_list_construct();
    }
    _set_adjacency_list_(arr_adjacency_lists);

    // build not connected graph
    _set_graph_vertices_(uf,  points, n_memb);

    // connect each node to another and sort them by distance
    edge** edge_arr = pascal_connections(points, n_memb);
   
    // build mst and tour
    unsigned short int max_edges = n_memb - 1;
    unsigned short int edges = 0;
    unsigned int total_edges = pascal_size(n_memb);
    clock_t mst_clk = clock();

    for(unsigned int i = 0; i < total_edges; i++){
        if(edges < max_edges){
            edge* current_edge = edge_arr[i];
            unsigned short int vertex1_idx = edge_get_node1_idx(current_edge);
            unsigned short int vertex2_idx = edge_get_node2_idx(current_edge);
            vertex* vertex1 = points[vertex1_idx];
            vertex* vertex2 = points[vertex2_idx];
            tree_node* tree_node1 = uf_find_node(uf, vertex_get_priority(vertex1));
            tree_node* tree_node2 = uf_find_node(uf, vertex_get_priority(vertex2));

            if(uf_union(uf, tree_node1, tree_node2) == True){
                _write_in_mst_file_(tsp_get_name(), vertex1_idx + 1, vertex2_idx + 1);
                printf("\n[%d] adjacency list: ", vertex1_idx);
                forward_list_push_front(arr_adjacency_lists[vertex1_idx], vertex2_idx);
                forward_list_print(arr_adjacency_lists[vertex1_idx], print_int);
                edges++;
            }
        }
        if(edges == max_edges){
            _end_clk_(mst_clk);
            edges++;            
        }
        edge_destroy(edge_arr[i]);
    }

    _write_in_mst_file_(tsp_get_name(), limit, limit);
    free(edge_arr);
    free(tsp_get_name());
    _end_profile_();
    // _adjacency_list_destroy_(n_memb);
    return uf;
}