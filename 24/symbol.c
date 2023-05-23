#include "symbol.h"

char operatorToChar(operator op) {
    switch(op) {
        case operatorMinus:
        case operatorDiv:
        case operatorMult:
        case operatorPlus:
        case operatorPow:   
            return op;
        case operatorUnaryMinus:
            return '-';
    }
    return - 1;
}


int nextChar() {
    int c;
    while(isspace(c = getchar())) {}
    return c;
}

bool nextSymbol(symbol* out) {
    static symbType prevType = symbNone;
    int c = nextChar();

    if (c == EOF) {
        out->type = symbNone;
        prevType = symbNone;
        return false;
    } else if (c == '.' || (c >= '0' && c <= '9')) {
        ungetc(c, stdin);
        out->type = symbNum;
        scanf("%f", &(out->data.number));
    } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        ungetc(c, stdin);
        out->type = symbVar;
        scanf("%[a-zA-Z]", out->data.var);
    } else if (c == '(') {
        out->type = symbLeftBracket;
    } else if (c == ')') {
        out->type = symbRightBracket;
    } else if (c == '+' || c == '-' || c == '/' || c == '^') {
        out->type = symbOperator;
        if (prevType == symbOperator || prevType == symbNone) {
            out->data.op = operatorUnaryMinus;
        } else {
            out->data.op = operatorMinus;
        }
    } else {
        out->type = symbNone;
        out->data.c = c;
    }
    prevType = out->type;
    return true;
}

int opPriority(char op) {
    switch(op) {
        case operatorMinus:
        case operatorPlus:
            return 1;
        case operatorMult:
        case operatorDiv:
            return 2;
        case operatorPow:
            return 3;
        case operatorUnaryMinus:
            return 4;
    }
    return -1;
}
