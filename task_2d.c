// Exercise 2d. Hash Tables - Test Driver
// Created by Russell Sammut-Bonnici on 25/12/2017.
// CPS1011

#include "hashTable.h"

//main method
int main(){

    //create and initialize hashTable1 with the pre-defined hash space 10
    HashTable * hashTable1 = createHashTable_S();

    //initializing array to store string key inputs (in this case IDs)
    char *key1[INPUT_AMOUNT]={"0426298M","0326288M","0134566M","0987654M","0234211M",
                              "0423458M","0234288M","0134098M","0456654M","0214211M",
                              "2345698M","0678348M","0223366M","0999954M","0121211M",
                              "0010108M","0234018M","0014098M","0972654M","0211111M"};

    //initializing array to store string value inputs (in this case Mobile No.s)
    char *value1[INPUT_AMOUNT]={"79835334","99887766","79856342","99223344","79887766",
                                "79567834","99333366","79111112","99113114","79000000",
                                "79835335","79835337","79835336","99222332","79563366",
                                "79874534","95692366","79109422","92376314","79000943"};

    //inserts keys and values into hashTable demonstrating insertion
    for(int i=0;i<INPUT_AMOUNT;i++) //loops for every pair input
        insertPair(hashTable1,key1[i],value1[i]);

    printf("\n");

    //deletes a specified pair in hashTable by scanning through list demonstrating deletion
    deletePair(hashTable1,"0972654M"); //deletes pair (which is "0972654M","92376314")

    printf("\n");

    //checks if key "0326288M" exists, returns 1 since it exists, demonstrating look up
    printf("Look up of key: \"%s\". Return value: %d\n","0326288M",checkExists(hashTable1,"0326288M"));

    printf("\n");

    //saves hashTable to disk as fileName
    saveHashTableAs(hashTable1,"hashTable1.dat");

    printf("\n");

    //loads "hashTable2" from disk by fileName and adds to hashTable
    loadHashTableTo("hashTable2.dat",hashTable1);

    printf("\n");

    //frees data in hashTable
    freeHashTable(hashTable1);

    return 0;
}