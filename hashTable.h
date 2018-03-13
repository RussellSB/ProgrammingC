// Exercise 2d. Hash Tables - Library linking and API
// Created by Russell Sammut-Bonnici on 25/12/2017.
// CPS1011

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* constant declaration */
#define INPUT_AMOUNT 20 //amount of pairs to be inputted to test the hashMap
#define HASH_SPACE 10 //pre-fixed hash_space defined as 10
#define MAX_COLL 6 //pre-fixed max_collisions defined as 6
#define INITIAL_MAX_C 3 //maximum collisions initially set to 3 (then grows dynamically)

/* struct declaration*/
typedef struct pair Pair; //creating struct for storing key-value pair
typedef struct bucket Bucket; //creating struct for linked list including its head
typedef struct hashTable HashTable; //creating struct for hashTable including pointer to row and hashSpace size
typedef struct node Node; //creating a struct for elements and their pointers inside singly linked lists
typedef struct list List; //creating struct for linked list including its head

/* function declaration for hashTable*/
HashTable * createHashTable_S(); //used for making static hashTable, using pre-defined constants
HashTable * createHashTable_D(unsigned int hashSpace); //used for making dynamic hashTable, initialising pointer hashTable by hashSpace as a parameter
int hashFunction_S(const char * keyIn); //used for returning hash value with pre-defined HASH_SPACE in static 2D array version
int hashFunction_D(HashTable * hashTable, const char * keyIn); //returns calculated hash value with relation to hash space
int insertPair(HashTable * hashTable,const char * key, const char * value); //inserts a pair to dynamic hashTable
int deletePair(HashTable * hashTable, const char * key); //deletes a pair from dynamic hashTable
int checkExists(HashTable * hashTable, const char * key); //looks up to see if an inputted key pair exists in dynamic hashTable
int saveHashTableAs(HashTable * hashTable,const char * fileName); //saves dynamic hashTable
int loadHashTableTo(const char *fileName,HashTable * hashTable); //loads dynamic hashTable
int freeHashTable(HashTable * hashTable); //frees space allocated during creation

#endif //HASHTABLE_H
