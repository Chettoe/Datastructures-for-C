#include "edge_graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void _test_add_edge();
void _test_get_edge();
void _test_deep_copy();

void test(void){
    _test_add_edge();
    _test_get_edge();
    _test_deep_copy();
    printf("Tests finished!\n");
}

void _test_add_edge(){
    EdgeGraph g;
    edge_graph_init(&g, 10, true);
    edge_graph_add_edge(&g, 0, 1);
    edge_graph_add_edge(&g, 1, 2);
    edge_graph_add_edge(&g, 2, 3);

    assert(((Edge*)g.edges->array[0])->index == 0);
    assert(((Edge*)g.edges->array[0])->source == 0);
    assert(((Edge*)g.edges->array[0])->target == 1);

    assert(((Edge*)g.edges->array[1])->index == 1);
    assert(((Edge*)g.edges->array[1])->source == 1);
    assert(((Edge*)g.edges->array[1])->target == 2);

    assert(((Edge*)g.edges->array[2])->index == 2);
    assert(((Edge*)g.edges->array[2])->source == 2);
    assert(((Edge*)g.edges->array[2])->target == 3);
    
    edge_graph_destroy(&g);
}

void _test_get_edge(){
    EdgeGraph g;
    edge_graph_init(&g, 10, true);
    edge_graph_add_edge(&g, 0, 1);
    edge_graph_add_edge(&g, 1, 2);
    edge_graph_add_edge(&g, 2, 3);

    Edge* a = edge_graph_get_edge(&g, 0);
    Edge* b = edge_graph_get_edge(&g, 1);
    Edge* c = edge_graph_get_edge(&g, 2);

    assert(a->source == 0 && a->index == 0 && a->target == 1);
    assert(b->source == 1 && b->index == 1 && b->target == 2);
    assert(c->source == 2 && c->index == 2 && c->target == 3);

    edge_graph_destroy(&g);
    free(a);
    free(b);
    free(c);
}

void _test_deep_copy(){
    EdgeGraph g;
    edge_graph_init(&g, 10, true);
    edge_graph_add_edge(&g, 0, 1);
    edge_graph_add_edge(&g, 1, 2);
    edge_graph_add_edge(&g, 2, 3);
    EdgeGraph* copy = edge_graph_deep_copy(&g);

    Edge* a_g = edge_graph_get_edge(&g, 0);
    Edge* b_g = edge_graph_get_edge(&g, 1);
    Edge* c_g = edge_graph_get_edge(&g, 2);

    Edge* a_copy = edge_graph_get_edge(&g, 0);
    Edge* b_copy = edge_graph_get_edge(&g, 1);
    Edge* c_copy = edge_graph_get_edge(&g, 2);

    assert(a_g->index == a_copy->index);
    assert(b_g->index == b_copy->index);
    assert(c_g->index == c_copy->index);

    assert(a_g->source == a_copy->source);
    assert(b_g->source == b_copy->source);
    assert(c_g->source == c_copy->source);

    assert(a_g->target == a_copy->target);
    assert(b_g->target == b_copy->target);
    assert(c_g->target == c_copy->target);

    edge_graph_destroy(&g);
    edge_graph_destroy(copy);
    free(copy);
    free(a_g);
    free(b_g);
    free(c_g);
    free(a_copy);
    free(b_copy);
    free(c_copy);
}