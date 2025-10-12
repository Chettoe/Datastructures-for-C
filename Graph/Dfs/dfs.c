#include "dfs.h"
#include "adj_array_graph.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void _dfs(AdjArrayGraph* g, size_t v, bool* seen, size_t* pred){
    seen[v] = true;
    printf("Besuche: %lu\n", v);

    for(int i = 0; i < adj_array_graph_degree(g, v); ++i){
        const int w = adj_array_graph_adj(g, v, i);
        if(!seen[w]){
            pred[w] = v;
            _dfs(g, w, seen, pred);
        }
    }
}

void dfs(AdjArrayGraph* g){
    bool* seen = calloc(g->n_nodes, sizeof(bool));
    size_t* pred = calloc(g->n_nodes, sizeof(size_t));

    for(size_t i = 0; i < g->n_nodes; ++i){
        if(!seen[i]) _dfs(g, i, seen, pred);
    }
    free(seen);
    free(pred);
}