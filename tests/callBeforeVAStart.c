#include "tests.h"

int sumPrint(int n, ...){
    va_list l;

    printf("Calling printf(..., 'x', 'y', 'z') and sum(10, 1, 2, ... 10) before calling va_start\n");
    printf("%c %c %c %d\n", 'x', 'y', 'z', sum(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

    va_start(l, n);
    dumpVAList(l);

    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += va_arg(l, int);
        dumpVAList(l);
    }

    va_end(l);
    return sum;
    
}

int main(){
    printf("Sum: 1+2+3 = %d\n", sumPrint(3, 1, 2, 3));
}