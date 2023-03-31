#ifndef deck_h
#define deck_h

#include <stdio.h>
#include <stdlib.h>
typedef struct elementDeck elementDeck;
typedef struct deck deck;

struct elementDeck { //структура элемента из дека
    int value; // значение
    elementDeck* next; //указатель на след элемент
    elementDeck* prev; //указатель на предыдущий элемент
};

struct deck { //структура дека
    int size; //размер
    elementDeck* first; //первый элемент
    elementDeck* last; //последний элемент
};

void initialisation(deck* D);
int empty(deck* D);
void pushFront(deck* D, int value);
void pushBack(deck* D, int value);
int popFront(deck* D);
int popBack(deck* D);
int top(deck* D);
int size(deck* D);
void printDeck(deck* D);
void cat(deck* D1, deck* D2);
void append(deck* D1, deck* D2);

#endif
