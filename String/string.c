#include <stdbool.h>
#include "string.h"
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

String* string(const char* word){
    String* s = malloc(sizeof(String));
    string_init(s, word);
    return s;
}

void string_init(String* str, const char* word){
    str->size = char_array_get_size(word);
    str->string = malloc(sizeof(char) * (str->size +1));
    check_memory(str->string);

    size_t index = 0;
    while(word[index] != '\0'){
        str->string[index] = word[index];
        ++index;
    }
    str->string[str->size] = '\0';
}

void string_destroy(String* str){
    free(str->string);
}

void check_memory(void* p){
    if(p == NULL){
        printf("No more memory\n");
    }
}

size_t char_array_get_size(const char* str){
    size_t length = 0;
    while(*str != '\0'){
        str++;
        ++length;
    }
    return length;
}

char string_get_index(const String* str, size_t index){
    assert(index < str->size);
    return str->string[index];
}

bool string_compare(const String* str1, const String* str2){
    if(str1 == NULL || str2 == NULL) return false;
    if(str1->size != str2->size) return false;
    
    return memcmp(str1->string, str2->string, str1->size) == 0;
}