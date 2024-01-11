#include "tests.h"

int sum5Times(int n, ...){
    va_list l, l2, l3, l4, l5; 
    va_start(l, n);
    dumpVAList(l);


    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += va_arg(l, int);
        dumpVAList(l);
    }
    va_start(l2, n);
    for(int i = 0; i < n; i++){
        sum += va_arg(l2, int);
        dumpVAList(l2);
    }
    va_start(l3, n);
    for(int i = 0; i < n; i++){
        sum += va_arg(l3, int);
        dumpVAList(l3);
    }
    va_start(l4, n);
    for(int i = 0; i < n; i++){
        sum += va_arg(l4, int);
        dumpVAList(l4);
    }
    va_start(l5, n);
    for(int i = 0; i < n; i++){
        sum += va_arg(l5, int);
        dumpVAList(l5);
    }

    va_end(l);
    va_end(l2);
    va_end(l3);
    va_end(l4);
    va_end(l5);
    return sum;
}

int main(){
    printf("Calling va_start 5 times\n");
    printf("Sum: 5*(1+2+3+...+100) = %d\n",
        sum5Times(100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
            21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
            40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
            59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
            78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
            97, 98, 99, 100));
}