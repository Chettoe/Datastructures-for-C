#include "edge_graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Edge* _get_copy(Edge* e);
void _check_memory_g(void* p);

void edge_graph_init(EdgeGraph* g, size_t n_edges, bool is_owner){
    g->edges = create_array_list(EDGE);
    g->n_nodes = n_edges;
    g->is_owner = is_owner;
}

EdgeGraph* create_edge_graph(size_t n_edges){
    EdgeGraph* g = malloc(sizeof(EdgeGraph));
    _check_memory_g(g);
    edge_graph_init(g, n_edges, true);
    return g;
}

void edge_graph_destroy(EdgeGraph* g){
    if(g->is_owner == false) return;
    for(int i = 0; i < g->edges->size; ++i){
        free(g->edges->array[i]);
    }
    free(g->edges->array);
    free(g->edges);
    g->edges = NULL;
    g->is_owner = false;
    g->n_nodes = 0;
}

void edge_graph_add_node(EdgeGraph* g){
    g->n_nodes++;
}

void edge_graph_add_edge(EdgeGraph* g, size_t source, size_t target){
    Edge* e = malloc(sizeof(Edge));
    _check_memory_g(e);
    e->source = source;
    e->target = target;
    e->index = g->edges->size;
    array_list_push_back(g->edges, e);
    free(e);
}

Edge* edge_graph_get_edge(EdgeGraph* g, size_t index){
    if(g->edges->size <= index) return NULL;
    return _get_copy(g->edges->array[index]);
}

EdgeGraph* edge_graph_deep_copy(EdgeGraph* g){
    EdgeGraph* copy = malloc(sizeof(EdgeGraph));
    copy->is_owner = true;
    copy->n_nodes = g->n_nodes;
    copy->edges = array_list_deep_copy(g->edges);
    return copy;
}

void edge_graph_print(EdgeGraph* g){
    for(size_t i = 0; i < g->edges->size; ++i){
        printf("src: %lu, tgt: %lu, idx: %lu\n", 
            ((Edge*) g->edges->array[i])->source, 
            ((Edge*) g->edges->array[i])->target, 
            ((Edge*) g->edges->array[i])->index);
    }
}

void _check_memory_g(void* p){
    if(p == NULL){
        printf("Memory Error!\n");
        assert(p != NULL);
    }
}

Edge* _get_copy(Edge* e){
    Edge* copy = malloc(sizeof(Edge));
    _check_memory_g(copy);
    memcpy(copy, e, sizeof(Edge));
    return copy;
}