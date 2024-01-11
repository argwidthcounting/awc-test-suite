#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int sumN( int n, ...) {
    va_list args;
    va_start(args, n);
    int sum = 0;
    
    for(int i = 0; i < n ; i ++) {
        sum += va_arg(args, int);
    }

    return sum ;
}

double sum0(){
    clock_t start, end;

    start = clock();

    for(int i = 0; i < 1000000; i++)
    {
        sumN(0);
    }

    end = clock();

    double result = ((double) end - start) / CLOCKS_PER_SEC;

    return result;
}

double sum3(){
    clock_t start, end;

    start = clock();

    for(int i = 0; i < 1000000; i++)
    {
        sumN(3, 1, 2, 3);
    }

    end = clock();

    double result = ((double) end - start) / CLOCKS_PER_SEC;

    return result;
}

double sum16(){
    clock_t start, end;

    start = clock();

    for(int i = 0; i < 1000000; i++)
    {
        sumN(16, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    }

    end = clock();

    double result = ((double) end - start) / CLOCKS_PER_SEC;

    return result;
}

double sum100(){
    clock_t start, end;

    start = clock();

    for(int i = 0; i < 1000000; i++)
    {
        sumN(100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 
                17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
                32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 
                47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 
                62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 
                77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 
                92, 93, 94, 95, 96, 97, 98, 99, 100);
    }

    end = clock();

    double result = ((double) end - start) / CLOCKS_PER_SEC;

    return result;
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s [0,3,16,100]\n", argv[0]);
        exit(-1);
    }

    if(argc >= 3){
        //This tests if AWC is enabled
        puts("Trying to crash with awc by running sumN with a size of 1, but no actual args; AWC will terminate, non-AWC will print another message\n");
        sumN(1);
        puts("Test failed, no AWC present\n");
        return 0;
    }

    int num = atoi(argv[1]);

    double result;

    switch(num){
        case 0:
            result = sum0();
            break;
        case 3:
            result = sum3();
            break;
        case 16:
            result = sum16();
            break;
        case 100:
            result = sum100();
            break;
        default :
            printf("Unknown number %d\n", num);
            exit(-1);
    }

    printf("%f seconds\n", result);
}