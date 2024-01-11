#include "tests.h"

int main(){
    printf("Calling printABunch with one too many args\n"); fflush(stdout);
    printABunch(7, "Hello, ", "how ", "are ", "you ", "today?", "\n");
    printf("You won't see this if AWC is working\n");
}