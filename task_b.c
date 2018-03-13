// Exercise 1b. Problem Solving
// Created by Russell Sammut-Bonnici on 09/11/2017.
// CPS1011

#include <stdio.h> //used for scanf() and printf()
#include <stdbool.h> //used for boolean
#include <ctype.h> //used for character validation
#include <mem.h> //used for strlen() function

#define DISCOUNT 0.05 //constant defining percentage discount

/* function declaration */
double calcCost(int amount,double cost_per_kg);
char getCharValidation();
int getIntValidation();
double calcShipping(int total_amount);

void printReceipt(int amount_a, int amount_b, int amount_c, double cost_a, 
                  double cost_b, double cost_c, int total_amount, double total_cost, 
                  double shipping_cost, bool discount, double cost_reduction);

int printReceiptToText(int amount_a, int amount_b, int amount_c, double cost_a,
                   double cost_b, double cost_c, int total_amount, double total_cost,
                   double shipping_cost, bool discount, double cost_reduction);

int main(){

    char input='x'; //input initially set as 0 so it isn't equal to 'q'
    char receipt; //input for if user wants a copy of the receipt or not

    int amount_a = 0;
    int amount_b = 0; //amounts of vegetables in kg initialised to 0
    int amount_c = 0;

    int temp; //temporarily stores inputted kg to accumulate to amount a,b or c

    double cost_a;
    double cost_b; //final price of vegetables
    double cost_c;

    double cost_reduction = 0; //cost reduction for when discount applies

    int total_amount; //stores total vegetable amount in kg
    double total_cost; //stores total order cost in euros
    double shipping_cost = 0; //shipping and handling cost

    bool discount = false; //boolean discount initialised for condition

    printf("Welcome to YourGreens.com!\n"); //welcome message
    printf("a) Artichokes\nb) Onions\nc) Carrots\nq) Proceed to checkout\n"); //displays menu

    //loop while input isn't 'q'
    while(input!='Q'){

        printf("Input a character to select an option:\n"); //prompt
        input = getCharValidation(); //scans char input, ignoring whitespaces after character
        input = (char)toupper(input); //changes to uppercase fo case in-sensitivity


        //using switch cases for choices
        switch(input){
            case 'A':
                printf("Enter the amount of artichokes desired in kg:\n"); //prompt

                //validates integer input and returns int to temp
                temp = getIntValidation();

                amount_a += temp; //accumulates total amount
                printf("You have %dkg of artichokes in your cart\n", amount_a);//outprints updated amount

                //breaks outside of switch case
                break;


            case 'B':
                printf("Enter the amount of onions desired in kg:\n");//prompt

                //validates integer input and returns int to temp
                temp = getIntValidation();

                amount_b += temp; //accumulates total amount
                printf("You have %dkg of onions in your cart\n", amount_b);//outprints updated amount

                //breaks outside of switch case
                break;

            case 'C':
                printf("Enter the amount of carrots desired in kg:\n");//prompt

                //validates integer input and returns int to temp
                temp = getIntValidation();

                amount_c += temp; //accumulates total amount
                printf("You have %dkg of onions in your cart\n", amount_c);//outprints updated amount

                //breaks outside of switch case
                break;

            case 'Q':
                printf("\nThank you for shopping with YourGreens.com!\n\n");
                break;//breaks outside of switch case

            default: //default case
                printf("Input not recognised! Select from the given list\n");//prompt
        }

    }

    //calculates total kg
    total_amount = amount_a + amount_b + amount_c;

    //calculates costs of each vegetable type
    cost_a = calcCost(amount_a,2.05);
    cost_b = calcCost(amount_b,1.15);
    cost_c = calcCost(amount_c,1.09);

    //calculates total vegetable cost
    total_cost = cost_a + cost_b + cost_c;

    //user gets 5% off Discount when order is 100 or more prior to shipping cost
    if(total_cost>=100) {
        discount = true; //set to true for condition when printing
        cost_reduction = total_cost * DISCOUNT;
        total_cost -= cost_reduction;
    }

    //calculates shipping cost and accumulates to total cost
    shipping_cost = calcShipping(total_amount);
    total_cost += shipping_cost;

    //structurally outprints receipt
    printReceipt(amount_a, amount_b, amount_c, cost_a, cost_b, cost_c, total_amount, total_cost, shipping_cost, discount, cost_reduction);


        printf("Would you like a copy of this receipt? (Y/N)\n"); //prompts user

    do {
        receipt = getCharValidation();

        if (receipt == 'Y' || receipt == 'y') { //user wants a copy of the receipt

            //structurally prints to receipt.txt file
            printReceiptToText(amount_a, amount_b, amount_c, cost_a, cost_b, cost_c, total_amount, total_cost,
                               shipping_cost, discount, cost_reduction);

            printf("Receipt printed.\n"); //confirms receipt was printed.

        } else if (receipt == 'N' || receipt == 'n') { //user doesn't want a copy of the receipt
            return 0;
        } else {
            printf("Input not recognised!\n");
            printf("Please enter 'Y' or 'N':\n");
        }
    }while(receipt != 'Y' && receipt != 'y' );

    return 0;
}

//method that calculates cost of vegetable type a,b or c
double calcCost(int amount,double cost_per_kg){
    return amount*cost_per_kg;
}

//method that validates character input and returns validated character
char getCharValidation() {

    int i; //used as counter for characters in input
    char ch; //inputted character

    do {
        //scans char input, ignoring whitespaces after character
        ch = (char)getchar();
        i=1; //i initialised to 1

        //checks if input is character
        if (isalpha(ch) == 0 || ch == '\n') {
            printf("Error: Input must be an alphanumeric character\n");
        }

        //counts inputted character stream in buffer
        while (getchar() != '\n') {
            i++;
        }

        //checks if input is not one character
        if (i != 1) {
            printf("Error: Input must be one character\n");
        }

    }while(isalpha(ch) != 0 && ch != '\n' && i != 1);

    return ch;
}

//method that gets integer after user validation process
int getIntValidation(){

    char term; //used for user validation for temp
    int temp; //used for temporarily storing amount

    if(scanf("%d%c", &temp, &term) != 2 || term != '\n'){//scans amount in kg and checks if int
        printf("Error: Amount must be an integer\n");
        return 0;
    }
    else if(temp<=0){ //checks if negative or nothing
        printf("Error: Amount exceeds possible range. Please enter a positive number\n");
        return 0;
    }
    else{
        return temp;
    }
}

//method that calculates shipping cost and returns it
double calcShipping(int total_amount){

    double shipping_cost = 0; //shipping and handling cost

    if(total_amount<=5) { //shipping cost is 6.50 eu when under 5 kg
        shipping_cost = 6.50;
        return shipping_cost;
    }
    else if(total_amount>5 && total_amount<20){ //shipping cost is 14 eu when over 5 kg but under 20 kg
        shipping_cost = 14;
        return shipping_cost;
    }
    else if(total_amount>=20){ //shipping cost is 14 + 0.50 Eur/kg when over 20 kg
        shipping_cost = 14 + 0.5*total_amount;
        return shipping_cost;
    }
}

//method that prints receipt requiring arguments for all the needed variables for doing so
void printReceipt(int amount_a, int amount_b, int amount_c, double cost_a, double cost_b, double cost_c,
                  int total_amount, double total_cost, double shipping_cost, bool discount, double cost_reduction){

    printf("---------Receipt-----------\n\t\tWEIGHT\tPRICE\n");

    printf("------------------------------\n");

    if(amount_a>0) //prints artichokes if added to cart
        printf("Artichokes:\t%dkg  \t%.2lfeu\n",amount_a,cost_a);
    if(amount_b>0) //prints onions if added to cart
        printf("Onions:    \t%dkg  \t%.2lfeu\n",amount_b,cost_b);
    if(amount_c>0) //prints carrots if added to cart
        printf("Carrots:   \t%dkg  \t%.2lfeu\n",amount_c,cost_c);

    printf("------------------------------\n");

    printf("Shipping:\t%dkg  \t%.2lfeu\n",total_amount,shipping_cost); //prints shipping cost

    printf("------------------------------\n");

    if(discount==true) //prints out discount when value is true i.e. cost >= 100 (used ASCII for %)
        printf("%c5 off\nDISCOUNT:\t\t%.2lfeu\n", 37, cost_reduction);

    printf("------------------------------\n");

    printf("Total:\t\t%dkg  \t%.2lfeu\n",total_amount,total_cost); //prints total
}

//method that prints receipt to text file, requiring all the needed variables for doing so
int printReceiptToText(int amount_a, int amount_b, int amount_c, double cost_a, double cost_b, double cost_c,
                       int total_amount, double total_cost, double shipping_cost, bool discount, double cost_reduction) {

    //declares file pointers and uses fopen() to open text file to write
    FILE *f;
    f = fopen("receipt.txt", "w");

    if (f == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    fprintf(f, "---------Receipt-----------\n\t\tWEIGHT\tPRICE\n");

    fprintf(f,"----------------------------\n");

    if(amount_a>0) //prints artichokes if added to cart
        fprintf(f, "Artichokes:\t%dkg  \t€%.2lf\n",amount_a,cost_a);
    if(amount_b>0) //prints onions if added to cart
        fprintf(f, "Onions:    \t%dkg  \t€%.2lf\n",amount_b,cost_b);
    if(amount_c>0) //prints carrots if added to cart
        fprintf(f, "Carrots:   \t%dkg  \t€%.2lf\n",amount_c,cost_c);

    fprintf(f,"----------------------------\n");

    fprintf(f, "Shipping:\t%dkg  \t€%.2lf\n",total_amount,shipping_cost); //prints shipping cost

    fprintf(f,"----------------------------\n");

    if(discount==true) //prints out discount when value is true i.e. cost >= 100 (used ASCII for %)
        fprintf(f, "%c5 off\nDISCOUNT:\t\t€%.2lf\n", 37, cost_reduction);

    fprintf(f,"----------------------------\n");

    fprintf(f, "Total:\t\t%dkg  \t€%.2lf\n",total_amount,total_cost); //prints total

    //closes file
    fclose(f);

}