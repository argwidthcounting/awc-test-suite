#include "tests.h"

int main(){
    printf("Calling sum with one too many args\n"); fflush(stdout);
    printf("Sum: 1+2+3+4 = %d\n", sum(4, 1, 2, 3));
    printf("You won't see this if AWC is working\n");
}