#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("FAIL: Please enter a string (input is passed as format string to printf!)\n");
        exit(-1);
    }

    printf("Printing your string as a format string\n");fflush(stdout);
    printf(argv[1]);
    printf("\nIf you entered a format string, you won't see this.\n");
}