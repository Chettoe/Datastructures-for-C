#ifdef RUN_TEST
#include "test_stack.h"
#define RUN_TEST_() test()
#else 
#define RUN_TEST_()
#endif

int main(void){
    RUN_TEST_();
    return 0;
}