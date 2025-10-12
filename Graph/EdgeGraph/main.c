#ifdef RUN_TEST
#include "test_edge_graph.h"
#define RUN_TEST_() test();
#else 
#define RUN_TEST_()
#endif

int main(void){
    RUN_TEST_();
    return 0;
}