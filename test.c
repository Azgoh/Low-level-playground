#include <stdio.h>

int check(int x){
    return x == 42 ? 1 : 0;
}


int main(void){

    int input;
    printf("Enter a number: ");
    scanf("%d", &input);

    check(input) ? printf("Correct!\n") : printf("Wrong!\n");

    return 0;
}