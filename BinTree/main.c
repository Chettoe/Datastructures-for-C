#ifdef RUN_TEST
#include "test_bin_tree.h"
#define RUN_TEST_ test_bin_tree();
#else
#define RUN_TEST_
#endif


int main(void){
    RUN_TEST_
    return 0;
}