#include "adj_array_graph.h"
#include "array_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _adj_array_graph_print_edge_array(ArrayList* al);
void _check_memory_g(void* p);
void* _get_copy_of_g(void* p, size_t data_size);

void adj_array_graph_init(AdjArrayGraph* g, bool is_owner){
    g->edges = create_array_list(EDGE);
    g->nodes = create_array_list(ARRAY_LIST);
    g->n_edges = 0;
    g->n_nodes = 0;
    g->is_owner = is_owner;
}

void adj_array_graph_destroy(AdjArrayGraph* g){
    if(g->is_owner == false) return;
    array_list_destroy(g->edges);
    free(g->edges);

    for(size_t i = 0; i < g->nodes->size; ++i){
        array_list_destroy(g->nodes->array[i]);
    }
    array_list_destroy(g->nodes);
    free(g->nodes);

    g->is_owner = false;
    g->n_edges = 0;
    g->edges = NULL;
    g->nodes = NULL;
}

AdjArrayGraph* create_adj_array_graph(){
    AdjArrayGraph* g = malloc(sizeof(AdjArrayGraph));
    _check_memory_g(g);
    adj_array_graph_init(g, true);
    return g;
}

void adj_array_graph_add_node(AdjArrayGraph* g){
    ArrayList* al = create_array_list(EDGE);
    array_list_push_back(g->nodes, al);
    free(al);
    g->n_nodes++;
}

void adj_array_graph_add_edge(AdjArrayGraph* g, size_t source, size_t target){
    if(source > g->nodes->size || target > g->nodes->size) return;
    Edge* e = malloc(sizeof(Edge));
    _check_memory_g(e);

    e->source = source;
    e->target = target;
    e->index = g->n_edges;
    g->n_edges++;

    array_list_push_back(g->edges, e);
    array_list_push_back(g->nodes->array[source], e);
    array_list_push_back(g->nodes->array[target], e);

    free(e);
}

//AdjArrayGraph* adj_array_graph_deep_copy(AdjArrayGraph* g){
//    AdjArrayGraph* copy = malloc(sizeof(AdjArrayGraph));
//    _check_memory_g(copy);
//    copy->edges = array_list_deep_copy(g->edges);
//
//    copy->nodes = malloc(sizeof(ArrayList*) * g->nodes->capacity);
//    _check_memory_g(copy->nodes);
//    copy->nodes->capacity = g->nodes->capacity;
//    copy->nodes->data_size = g->nodes->data_size;
//    copy->nodes->is_owner = true;
//    copy->nodes->size = g->nodes->size;
//
//    for(size_t i = 0; i < g->nodes->size; ++i){
//        copy->nodes[i].array = malloc(sizeof(Edge) * g->nodes[i].size);
//        for(size_t k = 0; k < g->nodes[i].size; ++k){
//            Edge* e = malloc(sizeof(Edge));
//            e->source = ((Edge*) g->nodes[i].array[k])->source;
//            e->target = ((Edge*) g->nodes[i].array[k])->target;
//            e->index = ((Edge*) g->nodes[i].array[k])->index;
//
//            copy->nodes[i].array[k] = e;
//        }
//    }
//
//    copy->n_nodes = g->n_nodes;
//    copy->n_edges = g->n_edges;
//    copy->is_owner = true;
//    return copy;
//}

void _adj_array_graph_print_edge_array(ArrayList* al){
    printf("[");
    for(size_t i = 0; i < al->size; ++i){
        if(i != 0) printf("\t\t ");
        printf("(");
        printf("Src: \t%lu Tgt: \t%lu Idx: \t%lu", 
            ((Edge*)al->array[i])->source, 
            ((Edge*)al->array[i])->target, 
            ((Edge*)al->array[i])->index);
        printf(")");
        if(i == al->size -1) break;
        printf("\n");
    }
    printf("]\n");
}

void adj_array_graph_print(AdjArrayGraph* g){
    printf("--------Adj-Graph------------------------------------\n");
    printf("Number of edges: %lu\tNumber of nodes: %lu\n\n", g->n_edges, g->n_nodes);

    printf("Edges -> \t");
    _adj_array_graph_print_edge_array(g->edges);

    printf("\nNodes -> \t");
    if(g->nodes->size == 0) printf("[]\n");
    for(size_t i = 0; i < g->nodes->size; ++i){
        _adj_array_graph_print_edge_array(g->nodes->array[i]);
        if(i == g->nodes->size -1) break;
        printf("\n\t\t");
    }
    printf("-----------------------------------------------------\n");
}

void _check_memory_g(void* p){
    if(p == NULL){
        printf("Memory Error!\n");
        assert(p != NULL);
    }
}

void* _get_copy_of_g(void* p, size_t data_size){
    void* copy = malloc(data_size);
    memcpy(copy, p, data_size);
    return copy;
}