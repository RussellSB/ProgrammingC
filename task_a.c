// Exercise 1a. Problem Solving
// Created by Russell Sammut-Bonnici on 08/11/2017.
// CPS1011

#include <stdio.h>

/* function declaration */
double calcInterest(double amount,int rate);

//main method to evaluate different interests through time and compare
int main(){
    int year = 1;
    double x = 200; //x stores Tom's simple interest, starts at principle
    double y = 200; //y stores Joan's compound interest, starts at principle

    //for loop that calculates interest every year until Joan overtakes Tom
    for(int i = year;y<=x;i++){

        //Tom
        x += calcInterest(200,15); //accumulates simple interest per year

        //Joan
        y += calcInterest(y,10); //accumulates compound interest per year


        //structurally outprints interests each year
        printf("----------Year %d----------\nTom\t\tJoan\n%.2lf\t\t%.2lf\n\n",i,x,y);


        //keeps track of years each iteration so that years can be read from outside the loop
        year = i;
    }

    //prints result
    printf("Joan's interest exceeds Tom's after %d years when Tom's is %.2lf and Joan's is %.2lf\n",year,x,y);

    return 0;
}

//method to calculate compound or simple interest for one year
double calcInterest(double amount,int rate){
    return amount * rate/100;
}