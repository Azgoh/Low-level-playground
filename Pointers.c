#include <stdio.h>

/*
A simple pointer arithmetic example showcasing
indirect access and modification to array elements via a pointer.
*/

int main() {
   
    int a[5] = {1,2,3,4,5};

    int *p = &a[0];
    printf("p[0] address is: %p\n", &p[0]);
    printf("p = %p\n", p);

    *(p+2) = 10;
    printf("a[2] is now: %d\n", a[2]);

    return 0;
}