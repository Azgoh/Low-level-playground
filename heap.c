#include <stdio.h>
#include <stdlib.h>

/*
*/

int main(void){

    int *a = malloc(4);
    int *b = malloc(4);

    printf("%p\n", a);
    printf("%p\n", b);

    free(a);
    free(b);

    return 0;
}