#include <stdio.h>
#include <stdlib.h>

/*
Showcasing the difference between the heap and the stack.

Local variables and function calls get allocated in the call stack.
It happens automatically when a function is called and is freed immediately 
when the function ends. It is fast and efficient but has limited space.
If too many function calls exceed the stack's capacity, it results in a stack
overflow error.

Heap memory on the other hand is allocated dynamically (malloc, calloc etc.).
Unlike stack memory, heap memory is not freed automatically when a function ends.
It requires manual deallocation in C and C++ or a garbage collector in Java or Python
to reclaim unused memory.
*/

int main(void){

    int a = 10; //stack
    int b = 20; // tack
    int *p = malloc(4); //heap
    *p = 30;

    printf("a address: %p\n", &a);
    printf("b address: %p\n", &b);
    printf("p heap address: %p\n", p);
    printf("p stack address: %p\n", &p);

    getchar();

    free(p); //free heap memory
    return 0;
}