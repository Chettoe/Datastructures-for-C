#ifndef EDGE_GRAPH_H
#define EDGE_GRAPH_H
#include <stdbool.h>
#include "array_list.h"

#define EDGE sizeof(Edge)

typedef struct Edge Edge;

typedef struct Edge{
    size_t source;
    size_t target;
    size_t index;
}Edge;

typedef struct EdgeGraph{
    ArrayList* edges;
    size_t n_nodes;
    bool is_owner;
}EdgeGraph;

void edge_graph_init(EdgeGraph* g, size_t n_edges, bool is_owner);
EdgeGraph* create_edge_graph(size_t n_edges);
void edge_graph_destroy(EdgeGraph* g);

void edge_graph_add_node(EdgeGraph* g);
void edge_graph_add_edge(EdgeGraph* g, size_t source, size_t target);
Edge* edge_graph_get_edge(EdgeGraph* g, size_t index);
EdgeGraph* edge_graph_deep_copy(EdgeGraph* g);
void edge_graph_print(EdgeGraph* g);

#endif