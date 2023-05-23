#ifndef symbol_h
#define symbol_h
#define LEN 10
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum opAssociation {
    assocLeft,
    assocRight
} opAssociation;

typedef enum symbType {
    symbNone,
    symbNum,
    symbVar,
    symbOperator,
    symbLeftBracket,
    symbRightBracket
} symbType;

typedef enum operator {
    operatorMinus = '-',
    operatorPlus = '+',
    operatorMult = '*',
    operatorDiv = '/',
    operatorPow = '^',
    operatorUnaryMinus = '!'
} operator;

typedef struct {
    symbType type;
    union {
        float number;
        char var[LEN];
        operator op;
        char c;
    } data;
} symbol;

int nextChar();
char operatorToChar(operator op);
bool nextSymbol(symbol* out);
int opPriority(char op);
#endif