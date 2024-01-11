#include "tests.h"

int main(){
    printf("Building the following string by passing chars to a variadic function\n"); fflush(stdout);
    char *s = buildStr(13, 'H', 'e', 'l', 'l', 'o', ' ', 'T', 'h', 'e', 'r', 'e', '\0');
    printf("\nYou won't see this if AWC is working\n");
    printf("I made the string \"%s\"\n", s);
    free(s);
}