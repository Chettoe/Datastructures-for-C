#ifndef ADJ_ARRAY_GRAPH_H
#define ADJ_ARRAY_GRAPH_H

#include <stdbool.h>
#include <stddef.h>
#include "array_list.h"

#define EDGE sizeof(Edge)
#define ARRAY_LIST sizeof(ArrayList)

typedef struct Edge{
    size_t source;
    size_t target;
    size_t index;
}Edge;

typedef struct AdjArrayGraph{
    ArrayList* nodes;
    ArrayList* edges;
    size_t n_edges;
    size_t n_nodes;
    bool is_owner;
}AdjArrayGraph;

void adj_array_graph_init(AdjArrayGraph* g, bool is_owner);
void adj_array_graph_destroy(AdjArrayGraph* g);
AdjArrayGraph* create_adj_array_graph();
void adj_array_graph_add_node(AdjArrayGraph* g);
void adj_array_graph_add_edge(AdjArrayGraph* g, size_t source, size_t target);

AdjArrayGraph* adj_array_graph_deep_copy(AdjArrayGraph* g);
void adj_array_graph_print(AdjArrayGraph* g);


#endif