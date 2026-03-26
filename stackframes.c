#include <stdio.h>

/* 
A simple example showcasing that foo has its own stack frame
Addresses in foo != addresses in main
*/

void foo(int x) {
    int y = 50;
    printf("foo -> x: %p, y: %p\n", &x, &y);
}

int main() {
    int a = 10;
    printf("main -> a: %p\n", &a);

    foo(a);

    return 0;
}