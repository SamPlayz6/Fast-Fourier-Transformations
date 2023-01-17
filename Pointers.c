#include "stdio.h"

void swap(int* n1, int* n2){
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
void addOne(int* ptr){
    (*ptr)++;
}

int main () {
    int num1 = 2, num2 = 10;
    swap(&num1,&num2);
    printf("Num1: %d Num2: %d\n",num1,num2);


    int* ptr, i = 9;
    ptr = &i;
    addOne(ptr);
    printf("Value of i: %d\n", *ptr);

   return 0;
}