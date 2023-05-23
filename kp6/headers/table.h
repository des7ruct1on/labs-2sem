#ifndef table_h
#define table_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abiturient.h"

#define TABLESIZE 100

typedef unsigned int uint;


typedef struct hashNode {
    void* data;
    struct hashNode* next;
} hashNode;

typedef struct hashTable {
    hashNode** table;
    size_t size;
} hashTable;

uint hash(hashTable* t, const char* str);
hashTable* initTable(size_t size);
hashNode* newHtableNode(void* data);
hashNode* htableGetFirst(hashTable *table, const char* key);
void htableInsert(hashTable* t, const char* key, void* data);
void hashTableFree(hashTable* table);
float calculateAverageBalls(hashTable* table);
float calculateOverallAverage(hashTable* table);
void findAbiturients(hashTable* table, float overallAverage);
hashNode* getNext (hashNode* node);
hashNode* htGetNext (hashNode* node);
hashNode* getLast (hashNode* node);
void* getData(hashNode* node);
void freeHashTable(hashTable* ht);
int printTable(hashTable* t);
#endif