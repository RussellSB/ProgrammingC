// Exercise 1d. Problem Solving
// Created by Russell Sammut-Bonnici on 21/11/2017.
// CPS1011

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUTFILE "inputText_d.txt" //constant defining input file
#define OUTPUTFILE "outputText_d.txt" //constant defining output file
#define MAX_L 1000 //sets max length for string

/* function declaration */
void replace(char * string, char * typo, char * correction);
char getCharValidation();
int confirmPrompt();
void printToTextFile(char *string);
void correctSpaceCommaFullstop(char * string);
void correctMultipleSpaces(char * string);
void correctMissingSpaces(char *string);

int main() {

    char string[MAX_L] = ""; //char array called string stores text file, initialised to empty to avoid garbage characters
    int i = 0; //counter for array string

    //INPUTFILE name and file pointers
    //character arrays store each character after reading the textFiles
    char ch;
    FILE *f;
    f = fopen(INPUTFILE, "r");

    //Reading input text file using file pointer and methods from <string.h>
    if (f != NULL) {
        //while read character isn't at the end of file, loop
        //scanning every character until the end of file
        while ((ch = (char) fgetc(f)) != EOF) {
            string[i] = ch;
            i++;
        }
    } else //exception of retrieval failure
    {
        printf("Error: \"%s\" was not found.\n", INPUTFILE);
        return 1;
    }

    fclose(f);

    //prints string, that is the text file
    printf("%s\n", string);
    printf("----------------------------------------\n");

    //calls auto-correct methods
    correctSpaceCommaFullstop(string);
    correctMultipleSpaces(string);
    correctMissingSpaces(string);

    //print to text file
    printToTextFile(string);
    printf("The corrected string has been saved to \"%s\"\n",OUTPUTFILE);


    return 0;
}

//method that searches and replaces substring in string string
void replace(char * string, char * typo, char * correction) {

    //a temp variable to do all replace things
    char temp[MAX_L];
    //to store what is returned from base case strstr()
    char * pointer;

    //base case
    if(!(pointer = strstr(string, typo)))
        return;

    //copy all the content to temp before the first occurrence of the typo string
    strncpy(temp, string, pointer-string);

    //prepare the temp for appending by adding a null to the end of it
    temp[pointer-string] = 0;

    //append using sprintf() function
    sprintf(temp+(pointer - string), "%s%s", correction, pointer + strlen(typo));

    //empty string for copying
    string[0] = 0;
    strcpy(string, temp);

    //pass recursively to replace other occurrences
    return replace(string, typo, correction);
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

//method that returns 1 when confirmed
int confirmPrompt(){

    char confirmation;

    printf("Would you like to auto-correct this typo? (Y/N):\n");

    //do while loop so that it loops until character is recognised
    do {

        confirmation = getCharValidation();

        if (confirmation == 'y' || confirmation == 'Y') {
            return 1;
        } else if (confirmation == 'n' || confirmation == 'N') {
            printf("Confirmed. The typo has been left as before.\n");
        } else {
            printf("Error: input not recognised.\n");
            printf("Please enter a recognised character (Y/N).\n");
        }
    }while(confirmation != 'n' && confirmation != 'N');
}

void printToTextFile(char *string){
    //opens output text file, prepared for writing
    FILE *f;
    f = fopen(OUTPUTFILE, "w");

    if (f == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    //prints auto-corrected string to text file
    fprintf(f, string);

    //closes file
    fclose(f);
}

//method that auto-corrects space before commas and fullstops
void correctSpaceCommaFullstop(char * string){

    //if statement checks for space before comma or a full stop
    if( strstr(string," ,") || strstr(string," .") ){
        printf("Error: Space before comma or a full-stop\n");

        //if confirmed program fixes typo
        if(confirmPrompt()==1){

            //replaces typos with correction
            replace(string," ,",",");
            replace(string," .",".");

            printf("Confirmed. The typos have been auto-corrected.\n");
            printf("----------------------------------------\n");
            //prints string, that is the text file
            printf("%s\n",string);
            printf("----------------------------------------\n");
        }
    }
}

//method that auto-corrects multiple spaces
void correctMultipleSpaces(char * string) {

    //if statement checks for multiple spaces
    if (strstr(string, "  ")) { //finds more than one space
        printf("Error: Multiple spaces as opposed to a single space\n");

        //if confirmed program fixes typo
        if (confirmPrompt() == 1) {

            //declaring variables
            char *from, *to;
            int spc = 0;

            //establishing unification
            to = from = string;

            //loop to auto-correct multiple spaces
            while (1) {
                if (spc && *from == ' ' && to[-1] == ' ')
                    ++from;
                else {
                    spc = (*from == ' ') ? 1 : 0;
                    *to++ = *from++;
                    if (!to[-1])
                        break;
                }
            }

            printf("Confirmed. The typos have been auto-corrected.\n");
            printf("----------------------------------------\n");
            //prints string, that is the text file
            printf("%s\n", string);
            printf("----------------------------------------\n");
        }
    }
}

void correctMissingSpaces(char *string) {

    char word[50] = ""; //char array for storing words from the text
    char correction[50]; //input for replacement of word

    //initialise 2D char array (String array) to store typos when found
    char typo[50][50] = {'\0'};

    int i = 0; //counter used for string array index
    int j = 0; //counter used for storing current words length
    int n = 0; //counter used for typo array

    //while loop scans for typo until the end of the text string (the end of its length)
    while (i < strlen(string)) {

        //while loop builds up word from characters until scanning a space/punctuation
        while (string[i] != ' ' && string[i] != '.' && string[i] != ',' && string[i] != '!' && string[i] != '\n') {
            word[j] = string[i];
            j++;
            i++;
        }


        //if word is more than 12 characters and no '-' then word typo is found so it is stored
        if (j > 12 && (strstr(word, "-") == 0)) {

            //stores typo from word into array
            strcpy(typo[n], word);
            n++;
        }

        //clear contents within word and iterates location to scan next word
        memset(word, 0, strlen(word));
        j = 0;
        i++;

    }

    //detect error when 1 or more typos are found
    if (n > 0) {

        printf("Error: Missing spaces\n");
        printf("Words longer than 12 characters and not including a hyphen (-) are rare\n");

        if (n == 1) //singular
            printf("%d typo of this case was found.\n", n);
        else //plural
            printf("%d typos of this case were found.\n", n);

        //loop for each typo
        for (i = 0; i < n; i++) {
            printf("Typo %d: ", i + 1);
            printf("The detected word was: \"%s\"\n", typo[i]);

            //if confirmed program fixes typo
            if (confirmPrompt() == 1) {

                printf("Input below the correction for \"%s\"\n", typo[i]);

                //scans so that spaces corrected between words are accepted
                scanf("%[^\n]%*c", correction);

                //replaces typo with correction
                replace(string, typo[i], correction);

                printf("Confirmed. The typo has been auto-corrected.\n");
                printf("----------------------------------------\n");
                //prints string, that is the text file
                printf("%s\n", string);

                printf("----------------------------------------\n");
            }

        }
    }
}
