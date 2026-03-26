#include <stdio.h>
#include <stdlib.h>

/*
Example of dynamic memory allocation on the heap.
Shows malloc and free and how each allocation gets a unique address.
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