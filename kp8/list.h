#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //структура списка
    char data; //литера
    struct node* prev; //указатель на предыдущий
    struct node* next; //указатель на следующий
} Node;

void pushFront(Node** head, char data);
void pushBack(Node** head, char data);
void pushIndex(Node** head, char data, int k);
void deleteBack(Node** head);
void deleteFront(Node** head);
void deleteIndex(Node** head, int k);
void swap(Node** head, int k);
void printList(Node* head);
void destroy(Node* head);
int sizeList(Node* head);

#endif