#include "stack.h"

stack* stackCreate() {
    stack* s = (stack*)malloc(sizeof(stack));
    s->top = NULL;
    s->size = 0;
    return s;
}

int stackEmpty(stack* s) {
    return s->size == 0;
}

void stackPush(stack* s, symbol value) {
    stackNode* tmp = (stackNode*)malloc(sizeof(stackNode));
    tmp->prev = s->top;
    tmp->value = value;
    s->top = tmp;
    s->size++;
}

int stackSize(stack* s) {
    return s->size;
}

symbol stackTop(stack* s) {
    if(stackEmpty(s)) {
        printf("Стек пуст!\n");
        return 0;
    }
    return s->top->value;
}
symbol stackPop(stack* s) {
    if (stackEmpty(s)) {
        printf("Стек пуст!\n");
        return 0;
    }
    symbol result = stackTop(s);
    stackNode* tmp = s->top;
    s->top = s->top->prev;
    free(tmp);
    s->size--;
    return result;
}

void stackDestroy(stack* s) {
    while(!stackEmpty(s)) {
        stackPop(s);
    }
    free(s);
}