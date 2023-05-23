#ifndef stack_h
#define stack_h

#include <stdbool.h>
#include "symbol.h"

typedef struct stackNode {
    symbol value;
    struct stackNode* prev; 
} stackNode;

typedef struct stack {
    stackNode* top;
    int size;
} stack;

stack* stackCreate();
int stackEmpty(stack* s);
void stackPush(stack* s, symbol value);
int stackSize(stack* s);
symbol stackTop(stack* s);
symbol stackPop(stack* s);
void stackDestroy(stack* s);

#endif