#include "tests.h"

double sumIntDoubleAlternate(int n, ...){
    va_list l; 
    va_start(l, n);
    dumpVAList(l);

    double sum = 0;
    for(int i = 0; i < n; i++){
        if(i % 2 == 0)
            sum += va_arg(l, int);
        else
            sum += va_arg(l, double);
        dumpVAList(l);
    }

    va_end(l);
    return sum;
}

int main()
{
    printf("Sum: 1 + 1.1 + 2 + 2.2 + ... + 12 + 12.12 = %f\n",
           sumIntDoubleAlternate(24, 1, 1.1, 2, 2.2,
                                 3, 3.3, 4, 4.4, 5, 
                                 5.5, 6, 6.6, 7, 7.7, 
                                 8, 8.8, 9, 9.9, 10, 
                                 10.10, 11, 11.11, 12, 12.12));
    printf("Added normally: %f\n", 1 + 1.1 + 2 + 2.2 +
                                 3 + 3.3 + 4 + 4.4 + 5 + 
                                 5.5 + 6 + 6.6 + 7 + 7.7 + 
                                 8 + 8.8 + 9 + 9.9 + 10 + 
                                 10.10 + 11 + 11.11 + 12 + 12.12);

}