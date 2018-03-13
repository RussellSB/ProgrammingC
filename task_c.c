//Exercise 1c. Problem Solving
//Created by Russell Sammut-Bonnici on 13/11/2017.
//CPS1011

#include <stdio.h>
#include <string.h> //for finding substring in string
#include <ctype.h> //for toupper() and isalpha()

#define INPUTFILE "inputText_2.txt" //constant defining file name

#define PHRASE_C "#include"
#define PHRASE_H1 "<html>"
#define PHRASE_H2 "</html>"

#define MAX_L 1000 //Max length of text file defined as 1000 characters

/* function declaration*/
int strstri(const char *haystackIn,const char *needleIn);

int main(){

    char string[MAX_L]; //char array called string stores text file
    int i=0; //counter for array string

    //we copy from const pointer to array to be able to use isupper()

    //declaring inputFile names and file pointers
    //character arrays store each character after reading the textFiles
    char ch;
    FILE *f;

    //Reading input text file using file pointer and methods from <string.h>
    if((f = fopen(INPUTFILE, "r")) != NULL)
    {
        //while read character isn't at the end of file, loop
        //scanning every character until the end of file
        while((ch = fgetc(f)) != EOF) {
            string[i]=ch;
            i++;
        }
    }
    else //exception of retrieval failure
    {
        printf("Error: %s was not found.\n", INPUTFILE);
        return 1;
    }

    //prints string, that is the text file
    printf("%s\n",string);
    printf("----------------------------------------\n");

    //strstr() returns true when it finds a substring in string (needle in a haystack)
    //strstri() works like strstr() except it is case-insensitive

    if(strstr(string, PHRASE_C) ) //if match is found at the beginning of string, it prints
        printf("The text file %s is a C source file.\n",INPUTFILE);
    else if( strstri(string,PHRASE_H1) && strstri(string, PHRASE_H2) ) //if both function statements for HTML returns true, it prints
        printf("The text file %s is an HTML file.\n",INPUTFILE);
    else //if conditions returns false, it prints
        printf("The text file %s is an unknown 'other type' of file.\n",INPUTFILE);

    //closes file
    fclose(f);

    return(0);
}

//method searches for case insensitive match, returns 1 (true) when match is found
int strstri(const char *haystackIn,const char *needleIn){

    //declare arrays
    char haystack[MAX_L];
    char needle[10];

    //copy string from pointer to arrays
    strcpy(haystack,haystackIn);
    strcpy(needle,needleIn);

    //changes needle to uppercase
    for(int i=0;i<strlen(needle);i++) {
        //converts character if alphanumeric
        if(isalpha(needle[i])!=0) {
            needle[i] = (char) toupper(needle[i]);
        }
    }

    //changes haystack to uppercase
    for(int i=0;i<strlen(haystack);i++) {
        //converts character if alphanumeric
        if(isalpha(haystack[i])!=0) {
            haystack[i] = (char) toupper(haystack[i]);
        }
    }

    //scans for case-insensitive match
    if(strstr(haystack,needle) )
        return 1;
}