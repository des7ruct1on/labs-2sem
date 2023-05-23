#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/table.h"
#include "../headers/abiturient.h"
uint hash(hashTable* t, const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % TABLESIZE;
}

hashTable* initTable(size_t size) {
    hashTable* table = malloc(sizeof(hashTable));
    table->table = calloc(size, sizeof(hashNode));
    table->size = size;
    return table;
}

hashNode* newHtableNode(void* data) {
    hashNode* newNode = malloc(sizeof(hashNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
hashNode* htableGetFirst(hashTable *table, const char* key) {
    int hashIndex = hash(table, key);
    hashNode **tmpTable = table->table;
    return tmpTable[hashIndex];
}
void htableInsert(hashTable* t, const char* key, void* data) {
    hashNode** table = t->table;
    int hashIndex = hash(t, key);
    hashNode* newNode = newHtableNode(data);
    hashNode* found = htableGetFirst(t, key);
    if (found != NULL) {
        hashNode* last = getLast(found);
        last->next = newNode;
        return;
    }
    table[hashIndex] = newNode;
    return;
}
void hashTableFree(hashTable* table) {
    for (int i = 0; i < table->size; i++) {
        hashNode* node = table->table[i];
        while (node != NULL) {
            hashNode* nextNode = node->next;
            free(node);
            node = nextNode;
        }
    }
    free(table->table);
    free(table);
}

float calculateAverageBalls(hashTable* table) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < table->size; i++) {
        hashNode* node = table->table[i];
        while (node != NULL) {
            abiturient* ab = (abiturient*)node->data;
            for (int j = 0; j < 20; j++) {
                sum += ab->balls.ball[j];
                count++;
            }
            node = node->next;
        }
    }
    return sum / count;
}

float calculateOverallAverage(hashTable* table) {
    float sum = 0;
    int count = 0;
    for (int i = 0; i < table->size; i++) {
        hashNode* node = table->table[i];
        while (node != NULL) {
            abiturient* ab = (abiturient*)node->data;
            sum += ab->examBall;
            count++;
            node = node->next;
        }
    }
    return sum / count;
}

void findAbiturients(hashTable* table, float overallAverage) {
    for (int i = 0; i < table->size; i++) {
        hashNode* node = table->table[i];
        while (node != NULL) {
            abiturient* ab = (abiturient*)node->data;
            float abAverage = 0;
            for (int j = 0; j < 20; j++) {
                abAverage += ab->balls.ball[j];
            }
            abAverage /= 20;
            if (strcmp(ab->medal, "No") == 0 && abAverage > overallAverage) {
                printf("%s %s\n", ab->surname, ab->initials);
            }
            node = node->next;
        }
    }
}

hashNode* getNext (hashNode* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

hashNode* htGetNext (hashNode* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

hashNode* getLast (hashNode* node) {
    hashNode* tmp = node;
    while (getNext(tmp) != NULL) {
        tmp = getNext(tmp);
    }
    return tmp;

}

void* getData(hashNode* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}

void freeHashTable(hashTable* ht) {
    if (ht == NULL) {
        return;
    }
    hashNode** table = ht->table;
    int size = ht->size;
    for (int i = 0; i < size; i++) {
        hashNode* node = table[i];
        while (node != NULL) {
            hashNode* tmp = node;
            node = node->next;
            free(tmp);
        }
        table[i] = NULL;
    }
    free(ht->table);
    free(ht);
}

void charsByStr(abiturient* s, char* str, size_t len) {
    if (s == NULL || str == NULL || len <= 0) {
        return;
    }
    snprintf(str, len, "")
}

int printTable(hashTable* t) {
    int res = 0;
    int size = t->size;
    hashNode** table = t->table;
    for (int i = 0; i < size; i++) {
        hashNode* curNode = table[i];
        if (curNode == NULL) {
            continue;
        }
        res++;
        printf("|===============================|\n");
        while(curNode != NULL) {
            abiturient* abit = getData(curNode);
            char* surname = getSurname(abit);
            char listChars[STRSIZE];
            listChars[STRSIZE - 1] = '\0';
            charsByStr(abit, listChars, STRSIZE);
            printf("|| %10s || %30s\n", surname, listChars);
            curNode = getNext(curNode);
        }
    }
    if (res) {
        printf("|===============================|\n");
    }
    return res;
}



