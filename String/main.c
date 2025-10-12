#include <assert.h>
#include <stdbool.h>
#include "string.h"
#include <stdlib.h>

void test(){
    String s;
    string_init(&s, "Hello");
    assert(s.size == 5);
    assert(string_get_index(&s, 1) == 'e');
    string_destroy(&s);

    String* s1 = string("Hehehe");
    assert(s1->size == 6);
    string_destroy(s1);
    free(s1);

    String* s2 = string("Hello");
    String* s3 = string("Hallo");
    String* s4 = string("Hi");
    String* s5 = string("Hello");
    assert(string_compare(s2, s3) == false);
    assert(string_compare(s3, s4) == false);
    assert(string_compare(s2, s5) == true);
    string_destroy(s2);
    string_destroy(s3);
    string_destroy(s4);
    string_destroy(s5);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
}

int main(void){
    test();
    return 0;
}