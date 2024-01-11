#include <stdio.h>
#include <stdarg.h>
#include "tests.h"

// Note that n should include the first 10
int sum10Plus(int n, int i1, int i2, int i3, int i4,
              int i5, int i6, int i7, int i8, int i9, int i10, ...)
{
    va_list l; 
    va_start(l, i10);
    dumpVAList(l);

    n = n - 10;
    int sum = i1 + i2 + i3 + i4 + i5 + i6 + i7 + i8 + i9 + i10;
    for(int i = 0; i < n; i++){
        int a = va_arg(l, int);
        sum += a;
        dumpVAList(l);
    }

    va_end(l);
    return sum;
}


int main()
{
    printf("Sum, but first 10 digits are required and not variadic\n");
    printf("Sum: 1+2+3...+100 = %d\n", sum10Plus(100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                                 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
                                                 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
                                                 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
                                                 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
                                                 98, 99, 100));
}