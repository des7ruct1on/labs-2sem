#ifndef tree_h
#define tree_h

#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    OP_PLUS = '+',
    OP_MINUS = '-',
    OP_MULTIPLY = '*',
    OP_DIVIDE = '/',
    OP_UNARY_MINUS ='!',
    OP_POW = '^'
} Operator;

typedef union {
    char c;
    float number;
    Operator op;
} SymbolData;

typedef enum {
    symb_NONE,
    symb_OP,
    symb_NUMBER,
    symb_VAR,
    symb_LEFT_BR,
    symb_RIGHT_BR
} SymbolType;

typedef struct {
    SymbolType type;
    SymbolData data;
} Symbol;

typedef struct Tree {
    Symbol value;
    struct Tree* parent;
    struct Tree* left;
    struct Tree* right;
} Tree;

typedef struct node { //структура двусвязного списка
    Symbol data;
    struct node* next;
    struct node* prev;
} node;

typedef enum { //типы данных для стека
    TREE,
    SYMBOL
} NodeType;

typedef union {
    char charValue;
    Tree* treeValue;
    Symbol symbolValue;
} NodeValue;

typedef enum {
    ASSOC_LEFT,
    ASSOC_RIGHT
} OperatorAssoc;

typedef struct stackNode {
    NodeType type;
    NodeValue value;
    struct stackNode* prev;
} stackNode;

typedef struct stack {
    stackNode* top;
    int size;
} stack;

OperatorAssoc op_assoc(char op);

Tree* createTree(Symbol value);
Tree* newNode(Tree* t, Symbol value);
void printTree(Tree* tree, int lvl);
void clearTree(Tree* tree);

void initStack(stack* s);
bool stackEmpty(stack* s);
int stackSize(stack* s);
void stackPushTree(stack* s, Tree* value);
void stackPushSymbol(stack* s, Symbol value);
Tree* stackPopTree(stack* s);
Symbol stackPopSymbol(stack* s);
void stackDestroy(stack* s);
Tree* stackTopTree(stack* s);
Symbol stackTopSymbol(stack* s);

void pushFront(node** head, Symbol data);
void pushBack(node** head, Symbol data);
void deleteBack(node* head);
void deleteFront(node* head);
void printList(node* head);
void destroy(node* head);
int sizeList(node* head);

bool isOperator(char ch);
int getPriority(char ch);
char oppToChar(Operator op);

#endif
