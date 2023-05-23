#ifndef abiturient_h
#define abiturient_h
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table.h"
#define STRSIZE 24

typedef int32_t Item;

typedef struct {
    char ob[20][STRSIZE];
    Item ball[20];
} subjectBall;

typedef struct abiturient {
    char surname[STRSIZE];
    char initials[STRSIZE];
    char sex[STRSIZE];
    Item schoolNum;
    char medal[STRSIZE];
    char composition[STRSIZE];
    Item examBall;
    subjectBall balls;
    hashTable* chars;
} abiturient;

char* getSurname(abiturient* s);
char* getInitials(abiturient* s);
abiturient* addAbiturient(const char* filename, char* in, hashTable* table);
abiturient* addAbiturientBin(const char* filename, char* in, hashTable* table);
int removeStudent(const char* file, const char* id); 
int removeStudentBin(const char* file, const char* id);
abiturient* newAbiturient();
void* getTableChars(abiturient* s, const char* key);
abiturient* addAbiturient(const char* filename, char* in, hashTable* table);
void printAbiturientChars(abiturient* s);
void abiturientFree(abiturient* s);
int csvRead(abiturient* abit, char* in);
void addReadAbitur(char* surname, char list[TABLESIZE][STRSIZE], int* count, hashTable* table);
int abiturientReadTxt(abiturient *s, FILE *in);
void abiturientWriteTxt(abiturient *s, FILE *file);
int abiturientReadBin(abiturient *s, FILE *in);
void abiturientWriteBin(abiturient *s, FILE *out);


#endif

