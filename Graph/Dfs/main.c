#include "adj_array_graph.h"
#include "array_list.h"
#include "dfs.h"
#include <stddef.h>
#include <stdlib.h>

int main(void){

    AdjArrayGraph* g = create_adj_array_graph();
    for(size_t i = 0; i < 20; ++i){
        adj_array_graph_add_node(g);
    }

    for(size_t i = 0; i < 20; ++i){
        adj_array_graph_add_edge(g, rand() % 20, rand() % 20);
    }

    dfs(g);

    adj_array_graph_destroy(g);
    free(g);
    
    return 0;
}