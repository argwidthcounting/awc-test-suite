#include "tests.h"

double sumDoubleIntAlternate(int n, ...){
    va_list l; 
    va_start(l, n);
    dumpVAList(l);

    double sum = 0;
    for(int i = 0; i < n; i++){
        if(i % 2 == 0)
            sum += va_arg(l, double);
        else
            sum += va_arg(l, int);
        dumpVAList(l);
    }

    va_end(l);
    return sum;
}

int main()
{
    printf("Sum: 0.0 + 1 + 2.2 + 3 + 4.4 + ... + 22.22 + 23 = %f\n",
           sumDoubleIntAlternate(24, 0.0, 1, 2.2, 3,
                                 4.4, 5, 6.6, 7, 8.8, 
                                 9, 10.10, 11, 12.12, 13, 
                                 14.14, 15, 16.16, 17, 18.18, 
                                 19, 20.20, 21, 22.22, 23));
    printf("Added normally: %f\n", 0.0 + 1 + 2.2 + 3 +
                                 4.4 + 5 + 6.6 + 7 + 8.8 + 
                                 9 + 10.10 + 11 + 12.12 + 13 + 
                                 14.14 + 15 + 16.16 + 17 + 18.18 + 
                                 19 + 20.20 + 21 + 22.22 + 23);
}