#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "symbol.h"
#include "stack.h"
#include "tree.h"

opAssociation opAssoc(operator o) {
    switch(o) {
        case operatorMinus:
        case operatorPlus:
        case operatorMult:
        case operatorDiv:
            return assocLeft;
        case operatorUnaryMinus:
        case operatorPow:
        return assocRight;
    }
    return -1;
}

int main() {
    stack* s;
    stack* rev;
    symbol t;

    s = stackCreate();
    rev = stackCreate();

    while(nextSymbol(&t)) {
        switch(t.type) {
            case symbNone:
                fprintf(stderr, "Ошибка! Символ не распознан\n");
                return 1;
            case symbOperator:
                for(;;) {
                    if(stackEmpty(s)) {
                        break;
                    }
                    symbol top = stackTop(s);
                    if(top.type != symbOperator) {
                        break;
                    }
                    if ((opAssoc(t.data.op) == assocLeft && opPriority(t.data.op) <= opPriority(top.data.op)) || (opAssoc(t.data.op) == assocRight && opPriority(t.data.op) < opPriority(top.data.op))) {
                        stackPop(s);
                        stackPush(rev, top);
                    } else {
                        break;
                    }
                }
                stackPush(s, t);
                break;
            case symbNum:
            case symbVar:
                stackPush(rev, t);
                break;
            case symbLeftBracket:
                stackPush(s ,t);
            case symbRightBracket:
                for(;;) {
                    if(stackEmpty(s)) {
                        fprintf(stderr, "Не закрыта скобка");
                        return 2;
                    }
                    symbol top = stackTop(s);
                    if(top.type == symbLeftBracket) {
                        stackPop(s);
                        break;
                    } else {
                        stackPop(s);
                        stackPush(rev, top);
                    }
                }
                break;
        }   
    }
    while (!stackEmpty(s)) {
        t = stackPop(s);
        if(t.type = symbLeftBracket) {
            fprintf(stderr, "Не закрыта скобка");
            return 2;
        }
        stackPush(rev, t);
    }

    if (stackEmpty(rev)) {
        fprintf(stderr, "Выражение пустое");
        return 3;
    }
    treeNode* root = NULL;
    if(!builtTree(&root, rev)) {
        fprintf(stderr, "Не найден один из операндов!");
        return 4;
    }
    if(!stackEmpty(rev)) {
        fprintf(stderr, "Найдены лишние операнды!");
        return 4;
    }

    printTree(root, 0);
    printExpr(root);
    printf("\n");
}