#include "tests.h"

#include <stdlib.h>

int main(int argc, char **argv){
    if(argc < 4){
        printf("FAIL: Please enter three numbers\n");
        exit(-1);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);

    printf("Sum: %d+%d+%d = %d\n", a, b, c, sum(3, a, b, c));
}