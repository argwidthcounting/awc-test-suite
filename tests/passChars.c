#include "tests.h"

int main(){
    printf("Building the following string by passing chars to a variadic function\n");
    char *s = buildStr(12, 'H', 'e', 'l', 'l', 'o', ' ', 'T', 'h', 'e', 'r', 'e', '\0');
    printf("I made the string \"%s\"\n", s);
    free(s);
}