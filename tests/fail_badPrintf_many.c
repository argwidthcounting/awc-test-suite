#include "tests.h"

int main(){
    printf("Calling printf with one too many format specifiers\n"); fflush(stdout);
    printf("Testing %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", 1, 2, 3);
    printf("You won't see this if AWC is working\n");
}