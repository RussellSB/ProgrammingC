// Exercise 2c. Hash Tables - linked list version
// Created by Russell Sammut-Bonnici on 20/12/2017.
// CPS1011

#include "hashTable.h"

//creating a struct Pair to store HashTable's values and keys
typedef struct pair{
    const char * key; //the key to be inputted
    const char * value; //the value to be inputted
}Pair;

//creating a struct for elements and their pointers inside singly linked lists
typedef struct node{
    Pair * data; //points to node's key and value
    struct node * next; //points to next node
}Node;

//creating struct for linked list including its head
typedef struct list{
    Node * head; //pointer to the head of the list
}List;

//creating struct for hashTable including pointer to head and hashSpace size
typedef struct hashTable{
    List **list; //double pointer to the beginning of the linked list
    int hashSpace; //size of the hashTable
}HashTable;

//initializes hashTable and allocates requested space from hashSpace
HashTable * createHashTable_D(unsigned int hashSpace){

    //allocating space for hashTable which is just 1 item
    HashTable * hashTable = calloc(1,sizeof(hashTable));

    //allocating space for number of lists, which are equal to the hashSpace
    hashTable->list = calloc(hashSpace, sizeof(Node));
    hashTable->hashSpace = hashSpace; //store hashSpace in hashTable

    return hashTable; //returns created hash Table
}


//method creates node that holds pair and adds to the list at head or tail
int insertPair(HashTable *hashTable, const char *key, const char *value) {

    int hashValue = hashFunction_D(hashTable, key); //hashValue for current insertion

    //If there is no list cause of no head, add head
    if (!hashTable->list[hashValue]) {

        hashTable->list[hashValue] = malloc(sizeof(List)); //allocate mem for new list

        if (hashTable->list[hashValue] == NULL) { //error check
            printf("Failed to allocate memory for new list at hashValue: %d.",hashValue);
            return 1;//fail
        }

        hashTable->list[hashValue]->head = malloc(sizeof(Node)); //allocate mem for new head

        if (hashTable->list[hashValue]->head->next == NULL) { //error check
            printf("Failed to allocate memory for new node at head.");
            return 1;//fail
        }

        hashTable->list[hashValue]->head->data = malloc(sizeof(Pair)); //allocate mem for new pair

        if (hashTable->list[hashValue]->head->data == NULL) { //error check
            printf("Failed to allocate memory for new pair at head.");
            return 1;//fail
        }

        hashTable->list[hashValue]->head->data->key = key; //set head key
        hashTable->list[hashValue]->head->data->value = value; //set head value
        hashTable->list[hashValue]->head->next = NULL; //set next of head to null for now

    } else { //if at tail aka when collision is detected

        Node *scan;//pointer scan used for navigating through the list
        scan = hashTable->list[hashValue]->head; //start scanning from head

        //navigate to the node at the end of the linked list (even at head)
        while(scan->next!=NULL){
            scan = scan->next; //point to next
        }

        //now we add new node to the end of the list
        scan->next = malloc(sizeof(Node)); //allocates memory for new node

        if (scan->next == NULL) { //error check
            printf("Failed to allocate memory for new node at tail.");
            return 1;//fail
        }

        scan->next->data = malloc(sizeof(Pair)); //allocate mem for new pair

        if (scan->next->data == NULL) { //error check
            printf("Failed to allocate memory for new pair at tail.");
            return 1;//fail
        }

        scan->next->data->key = key; //sets data key of new node
        scan->next->data->value = value; //sets data value of new node
        scan->next->next = NULL; //since last node, next node after it is set to null

    }

    printf("Pair of key: \"%s\" and value: \"%s\" was successfully inserted into the hashTable, hashValue: %d.\n",key,value,hashValue);
}

//method deletes pair held in linked list by key
int deletePair(HashTable * hashTable, const char * key){

    int r = hashFunction_D(hashTable,key); //keeps track of hashValue aka list number for pair deletion
    Node *scan = hashTable->list[r]->head; //set currNode to scan list, checking for match
    int stop = 0; //variable for stopping loop when set to 1 - when pair is deleted

    if(checkExists(hashTable,key)==1) { //deletes if requested key exists

        //navigate to the node at the end of the linked list checking for match and stop when match is found (even at head)
        while(scan!=NULL && stop!=1){

            if(strcmp(hashTable->list[r]->head->data->key,key)==0){ //delete at head

                if(hashTable->list[r]->head->next!=NULL){ //if list has more than head, need set head to node after it

                hashTable->list[r]->head = hashTable->list[r]->head->next; //remove head by overwriting it with next node

                }else { //if list just contains head, delete head then list
                    free(hashTable->list[r]->head); //deletes head where match is found
                    free(hashTable->list[r]); //free list

                }

                printf("Deletion of key: \"%s\" was successful at head.\n",key);

                stop=1; //exits loop

            }else if(strcmp(scan->next->data->key,key)==0&&scan->next->next!=NULL){ //delete in the middle

                scan->next = scan->next->next; //skips over deleted node
                free(scan->next); //deletes element where match is found

                printf("Deletion of key: \"%s\" was successful in middle.\n",key);

                stop=1; //exits loop

            }else if(strcmp(scan->next->data->key,key)==0&&scan->next->next==NULL){ //delete at tail

                scan->next = NULL; //sets pointer to deleted node to NULL
                free(scan->next); //deletes tail where match is found

                printf("Deletion of key: \"%s\" was successful at tail.\n",key);

                stop=1; //exits loop
            }

            if(stop!=1)
                scan = scan->next; //point to next
        }

    }

}

//method that goes through link checking if pair of entered key exists. returns 1 when exists
int checkExists(HashTable *hashTable,const char *key){

    int hashValue = hashFunction_D(hashTable,key);

    if(hashTable->list[hashValue]->head==NULL){//checks if list of hashValue exists
        printf("Error: the key's hashValue does not own any existing list.");
        return 0;
    }else{ //goes through list
        Node *scan = hashTable->list[hashValue]->head;

        while(scan!=NULL){ //loops to last node in the list (which can be the head)

            if(strcmp(scan->data->key,key)==0){

                return 1; //exists

            }

            scan = scan->next; //point to next

        }

        //at this point it has reached the end of the list without finding any match
        printf("Error: the key's hashValue does not own an existing list.");
        return 0;

    }

}

//method for hashFunction_D, accepts key and value as arguments
int hashFunction_D(HashTable * hashTable, const char * keyIn){

    int charSumKey = 0; //sum of the ASCII code of characters in key
    int x; //variable to be returned
    int size = hashTable->hashSpace; //sets size to hashSpace of table

    //accumulates sum of ASCII code of each character
    for(int i=0;i<strlen(keyIn);i++) {
        charSumKey += keyIn[i];
    }

    x = charSumKey % size; //invented formula for hash function
    return x;
}

int saveHashTableAs(HashTable * hashTable,const char * fileName){

    Node *scan;//pointer scan used for navigating through the list

    FILE *f;
    f = fopen(fileName,"w"); //opens new file to write to
    if(f!=NULL) {

        //loop by row
        for (int i = 0; i < hashTable->hashSpace; i++) {

            if(hashTable->list[i]!=NULL) { //if list exists

                scan = hashTable->list[i]->head; //start scanning from head

                //navigate to the end of the linked list (can be the head)
                while (scan!=NULL) {

                    fprintf(f, "%s,%s", scan->data->key, scan->data->value);
                    fprintf(f, "\t"); //new column
                    scan = scan->next; //point to next

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

    for(int i=0;i<hashTable->hashSpace;i++) { //frees every list if exists
        if(hashTable->list[i]!=NULL)
            free(hashTable->list[i]);
    }

    free(hashTable); //finally, frees hashTable

    printf("Current hashTable has been successfully freed.\n");

}
