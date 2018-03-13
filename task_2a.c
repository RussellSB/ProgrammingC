// Exercise 2a. Hash Tables - Fixed 2D Array version
// Created by Russell Sammut-Bonnici on 08/12/2017.
// CPS1011

#include "hashTable.h"

//creating a struct Pair to store HashTable's values and keys
typedef struct pair{
    const char * key; //the key to be inputted
    const char * value; //the value to be inputted
}Pair;

//creating struct for bucket including its head
typedef struct bucket{
    Pair ** pair; //pointer to data that is in pair
}Bucket;

//creating struct for hashTable including pointer to row
typedef struct hashTable{
    Bucket ** bucket; //double pointer to the beginning of the row
}HashTable;

//initializes hashTable and allocates requested space from hashSpace
HashTable * createHashTable_S(){

    //allocating space for hashTable which is just 1 item
    HashTable * hashTable = calloc(1,sizeof(hashTable));

    //allocating space for number of rows, which are equal to the hashSpace
    hashTable->bucket= calloc(HASH_SPACE, sizeof(Bucket));

    return hashTable; //returns created hash Table
}

//method that inserts pair into created hashTable
int insertPair(HashTable * hashTable,const char * key, const char * value){

    int hashValue = hashFunction_S(key); //calculate hashValue

    if(hashTable->bucket[hashValue]==NULL){//if bucket doesnt exist

        hashTable->bucket[hashValue] = malloc(sizeof(Bucket)); //allocate mem for new bucket

        if (hashTable->bucket[hashValue] == NULL) { //error check
            printf("Failed to allocate memory for new bucket at hashValue: %d.",hashValue);
            return 1;//fail
        }

        hashTable->bucket[hashValue]->pair = calloc(MAX_COLL, sizeof(Pair)); //allocate mem for three pairs in bucket

        if (hashTable->bucket[hashValue]->pair == NULL) { //error check
            printf("Failed to allocate memory for array of pairs at hashValue: %d.",hashValue);
            return 1;//fail
        }

        hashTable->bucket[hashValue]->pair[0] = malloc(sizeof(Pair)); //allocate mem for first pair
        hashTable->bucket[hashValue]->pair[0]->key = key; //set key of first pair
        hashTable->bucket[hashValue]->pair[0]->value = value; //set value of first pair

    }else if(hashTable->bucket[hashValue]!=NULL){ //if bucket exists

        int c=0; //collision counter to count amount of collisions in bucket when inserting

        while(hashTable->bucket[hashValue]->pair[c]!=NULL){ //while pair exists
            c++; //increment collision counter
        }

        if(c<MAX_COLL){ //if c is less than max initial collisions
            hashTable->bucket[hashValue]->pair[c] = malloc(sizeof(Pair)); //allocate mem for pair
            hashTable->bucket[hashValue]->pair[c]->key = key; //set key after last collision
            hashTable->bucket[hashValue]->pair[c]->value = value; //set value after last collision

        }else{ //if c is equal to the ax collisions, no space for new pair, produce error
            printf("Error: Max_Collisions %d exceeded.",MAX_COLL);
            return 1;
        }

    }

    printf("Pair of key: \"%s\" and value: \"%s\" was successfully inserted into the hashTable, hashValue: %d.\n",key,value,hashValue);

}

//method for hashFunction_S, accepts key and value as arguments
int hashFunction_S(const char * keyIn){

    int charSumKey = 0; //sum of the ASCII code of characters in key
    int x; //variable to be returned

    //accumulates sum of ASCII code of each character
    for(int i=0;i<strlen(keyIn);i++) {
        charSumKey += keyIn[i];
    }

    x = charSumKey % HASH_SPACE; //invented formula for hash function
    return x;
}

int deletePair(HashTable * hashTable, const char * key){

    int hashValue = hashFunction_S(key); //get hashValue

    if(checkExists(hashTable,key)==1){ //if exists, delete pair

        int c = 0; //counter for collision index
        int stop = 0; //to break from loop from if statement
        Bucket *scan = hashTable->bucket[hashValue];

        while(scan!=NULL && stop!=1){ //scans through list until match to delete is found

            if(strcmp(hashTable->bucket[hashValue]->pair[0]->key,key)==0){ //if match found at head

                if(hashTable->bucket[hashValue]->pair[1]==NULL){ //if head to delete is the only node in the bucket delete head then bucket

                    hashTable->bucket[hashValue]->pair[0]->key=NULL;
                    hashTable->bucket[hashValue]->pair[0]->value=NULL;
                    free(hashTable->bucket[hashValue]->pair[0]);
                    free(hashTable->bucket[hashValue]->pair);
                    free(hashTable->bucket[hashValue]);

                }else if(hashTable->bucket[hashValue]->pair[1]!=NULL){ //if there is more than just one node in the list, shift rest to left then delete last

                    while(scan->pair[c]!=NULL) { //while current node exists

                        if (scan->pair[c + 1] != NULL) { //if next node exists

                            scan->pair[c]->key = scan->pair[c + 1]->key; //copy, from next node to key
                            scan->pair[c]->value = scan->pair[c + 1]->value; //copy, from next node to value

                        }else{ //if next node doesn't exist (at end of list)

                            hashTable->bucket[hashValue]->pair[c]->key=NULL;
                            hashTable->bucket[hashValue]->pair[c]->value=NULL;
                            free(scan->pair[c]); //delete last element

                        }

                        c++; //increment counter

                    }
                }

                printf("Deletion of key: \"%s\" was successful at head.\n",key);
                stop=1; //stop scanning for match

            }else if(strcmp(scan->pair[c]->key,key)==0 && scan->pair[c+1]!=NULL){//if match found in middle, shift everything after it to the left

                while(scan->pair[c]!=NULL) { //while current node exists

                    if (scan->pair[c + 1] != NULL) { //if next node exists

                        scan->pair[c]->key = scan->pair[c + 1]->key; //copy, from next node to key
                        scan->pair[c]->value = scan->pair[c + 1]->value; //copy, from next node to value

                    }else{ //if next node doesn't exist (at end of list)

                        hashTable->bucket[hashValue]->pair[c]->key=NULL;
                        hashTable->bucket[hashValue]->pair[c]->value=NULL;
                        free(scan->pair[c]); //delete last element

                    }

                    c++; //increment counter

                }

                printf("Deletion of key: \"%s\" was successful in middle.\n",key);
                stop=1; //stop scanning for match

            }else if(strcmp(scan->pair[c]->key,key)==0 && scan->pair[c+1]==NULL){//if match found at end

                hashTable->bucket[hashValue]->pair[c]->key=NULL;
                hashTable->bucket[hashValue]->pair[c]->value=NULL;
                free(scan->pair[c]); //delete last element

                printf("Deletion of key: \"%s\" was successful.\n",key);
                stop=1; //stop scanning for match

            }else { //if match not found
                c++; //increment c
            }

        }

    }


}

//method that looks up key and checks if it exists in the hashTable, returns 1 when exists
int checkExists(HashTable * hashTable, const char * key){

    int hashValue = hashFunction_S(key); //get hashValue

    if(hashTable->bucket[hashValue]==NULL){//checks if bucket of hashValue exists
        printf("Error: the key's hashValue does not own any existing bucket.\n");
        return 0;
    }else{ //goes through bucket

        int c = 0; //collision index counter
        Pair *scan = hashTable->bucket[hashValue]->pair[c];

        while(scan!=NULL){ //loops to last node in the bucket (which can be the first pair)

            if(strcmp(scan->key,key)==0){

                return 1; //exists

            }

            c++; //increment c
            scan = hashTable->bucket[hashValue]->pair[c]; //goes to next column

        }

        //at this point it has reached the end of the bucket without finding any match
        printf("Error: the key's hashValue does not own an existing list.\n");
        return 0;

    }

}

//method that saves hashTable to structured text file
int saveHashTableAs(HashTable * hashTable,const char * fileName){

    FILE *f;
    f = fopen(fileName,"w"); //opens new file to write to
    if(f!=NULL) {

        //loop by row
        for (int i = 0; i < HASH_SPACE; i++) {

            if(hashTable->bucket[i]!=NULL) { //if bucket exists

                Bucket *scan = hashTable->bucket[i];
                int c=0; //collision counter index initialised

                //navigate to the end of the bucket (can be the head)
                while (scan->pair[c]!=NULL) {

                    fprintf(f, "%s,%s", scan->pair[c]->key, scan->pair[c]->value);
                    fprintf(f, "\t"); //new column

                    c++; //increment c
                }
            }

            fprintf(f,"\n"); //new row
        }


        printf("Hash table saved successfully to \"%s\"\n", fileName);
    }
}

//method that loads hashTable setting it to the current hashTable
int loadHashTableTo(const char *fileName,HashTable * hashTable){

    char ch; //temporarily stores character from file
    char string[1000]=""; //initialized string to temporarily hold text for scanning to max 1000 characters

    char word[30] = {'\0'};

    char key[30] = {'\0'}; //initialized to temporarily store key, max characters set to 30
    char value[30] = {'\0'}; //initialized to temporarily store key, max characters set to 30

    int i=0; //counts characters for string
    int j = 0; //counts characters for word

    FILE *f;
    f = fopen(fileName,"r"); //opens new file to write to

    //Reading input text file using file pointer and methods from <string.h>
    if(f != NULL)
    {
        //while read character isn't at the end of file, loop
        //scanning every character until the end of file
        while((ch = (char)fgetc(f)) != EOF) {
            string[i]=ch;
            i++;
        }
    }
    else //exception of retrieval failure
    {
        printf("Error: %s was not found.\n", fileName);
        return 1;
    }

    fclose(f); //fclose(f) to avoid memory leak

    i=0; //refreshing counter to be re-used in another while loop

    //scans string for words till the end, which are then sorted into keys and values
    while(i<strlen(string)){

        //nested while loop builds up word
        while(string[i]!=','&&string[i]!='\t'&&string[i]!='\n'){
            word[j]=string[i];
            j++; //increment char counter for word
            i++; //increment char counter for string
        }

        if(string[i]==','){
            for(int n=0;n<strlen(word);n++)
                key[n]=word[n];

        }else if(string[i]=='\t'){ //when after TAB it goes to next column or row
            //printf("value:%s",word);
            //printf("\tcolumn:%d\n",c);
            for(int n=0;n<strlen(word);n++)
                value[n]=word[n];

            if(strcmp(key,"(null)")!=0 && strcmp(value,"(null)")!=0) //only inserts when not null
                insertPair(hashTable,key,value);

            memset(key,0,strlen(key)); //refresh current key for next key
            memset(value,0,strlen(value)); //refresh current value for next value

        }

        memset(word,0,strlen(word)); //refresh current word for next word
        j = 0; //refresh char counter for word
        i++; //increment char counter for string
    }

    printf("\"%s\" loaded successfully to the current hashTable\n",fileName);

}

//method that frees the hashTable since memory was allocated to it when creating
int freeHashTable(HashTable * hashTable){

    for(int i=0;i<HASH_SPACE;i++) { //frees every bucket if exists
        if(hashTable->bucket[i]!=NULL)
            free(hashTable->bucket[i]);
    }

    free(hashTable); //finally, frees hashTable

    printf("Current hashTable has been successfully freed.\n");

}