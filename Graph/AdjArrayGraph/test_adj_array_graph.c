#include "test_adj_array_graph.h"
#include "adj_array_graph.h"
#include "array_list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void _test_init_destroy(void);
void _test_add_node(void);
void _test_add_edge(void);
void _test_deep_copy(void);
void _test_resize_with_add(void);

void test(void){
    _test_init_destroy();
    _test_add_node();
    _test_add_edge();
    //_test_deep_copy();
    _test_resize_with_add();
    printf("Test finished!\n");
}

void _test_init_destroy(void){
    AdjArrayGraph* g = create_adj_array_graph();
    adj_array_graph_destroy(g);
    free(g);
}

void _test_add_node(void){
    AdjArrayGraph* g = create_adj_array_graph();
    adj_array_graph_add_node(g);

    assert(g->nodes->size == 1);
    assert(g->n_nodes == 1);
    assert(g->n_edges == 0);

    adj_array_graph_destroy(g);
    free(g);
}

void _test_add_edge(void){
    AdjArrayGraph* g = create_adj_array_graph();
    adj_array_graph_add_node(g);
    adj_array_graph_add_node(g);
    adj_array_graph_add_node(g);

    assert(g->n_nodes == 3);
    assert(g->nodes->size == 3);
    assert(g->n_edges == 0);

    adj_array_graph_add_edge(g, 0, 1);
    adj_array_graph_add_edge(g, 0, 2);
    adj_array_graph_add_edge(g, 9999, 9999);

    assert(g->edges->size == 2);
    assert(g->n_edges == 2);

    size_t a = ((ArrayList*)g->nodes->array[0])->size;
    assert(a == 2);

    size_t b = ((ArrayList*)g->nodes->array[1])->size;
    assert(b == 1);

    size_t c = ((ArrayList*)g->nodes->array[2])->size;
    assert(c == 1);

    adj_array_graph_destroy(g);
    free(g);
}

//void _test_deep_copy(void){
//    AdjArrayGraph* g = create_adj_array_graph();
//    adj_array_graph_add_node(g);
//    adj_array_graph_add_node(g);
//    adj_array_graph_add_node(g);
//    adj_array_graph_add_edge(g, 0, 1);
//    adj_array_graph_add_edge(g, 0, 2);
//
//    AdjArrayGraph* copy = adj_array_graph_deep_copy(g);
//
//    assert(g->n_edges == copy->n_edges);
//    assert(g->n_nodes == copy->n_nodes);
//
//    adj_array_graph_destroy(g);
//    free(g);
//    adj_array_graph_destroy(copy);
//    free(copy);
//}

void _test_resize_with_add(void){
    AdjArrayGraph* g = create_adj_array_graph();
    for(size_t i = 0; i < 100; ++i){
        adj_array_graph_add_node(g);
    }
    adj_array_graph_add_edge(g, 0, 1);
    adj_array_graph_add_edge(g, 0, 2);
    adj_array_graph_add_edge(g, 2, 1);
    adj_array_graph_add_edge(g, 4, 7);
    adj_array_graph_add_edge(g, 7, 8);
    adj_array_graph_add_edge(g, 1, 8);
    adj_array_graph_add_edge(g, 8, 3);
    adj_array_graph_add_edge(g, 3, 6);

    adj_array_graph_destroy(g);
    free(g);
}