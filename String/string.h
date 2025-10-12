#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
typedef struct String{
    char* string;
    size_t size;
}String;
String* string(const char* word);
void string_init(String* str, const char* word);
void string_destroy(String* str);
void check_memory(void* p);

size_t char_array_get_size(const char* str);

char string_get_index(const String* str, size_t index);
bool string_compare(const String* str1, const String* str2);


#endif