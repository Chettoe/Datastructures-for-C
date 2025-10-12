#ifdef RUN_TEST
#include "list_test.h"
#define RUN_TEST_() test_list()
#else
#define RUN_TEST_()
#endif

int main(void){ 
    RUN_TEST_();
    return 0;
}