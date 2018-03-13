// Exercise 1e. Problem Solving
// Created by Russell Sammut-Bonnici on 07/12/2017.
// CPS1011

#include <stdio.h>

#define ARRAY_SIZE 10 //constant defining array size

/* function declaration */
void view_stack_frame(int array[]);

int main(){

    //declare array storing integer variables
    int collection[ARRAY_SIZE];

    //loop to automatically store varying values in the variables
    for(int i=0;i<ARRAY_SIZE;i++){
        collection[i] = i;
    }

    view_stack_frame(collection);
    return 0;
}

//view stack frame accepts array as an argument
void view_stack_frame(int array[]){

    //prints two columns
    printf("Address\t\tValue\n");
    printf("=======\t\t=====\n");

    //loops address and value contents of array
    for(int i=0;i<ARRAY_SIZE;i++){
        printf("%p\t%d\n",&array[i],array[i]);
    }

}


