#ifndef token_h
#define token_h
#define LEN 10
typedef enum opAssociation {
    assocLeft,
    assocRight
} opAssociation;

typedef enum tokenType {
    tokenNone, //не лексема
    tokenNum, //число
    tokenVar, //переменная
    tokenOperator, //оператор
    tokenLeftBracket, //левая скобка
    tokenRightBracket //правая скобка
} tokenType;

typedef enum operator {
    operatorMinus = '-',
    operatorPlus = '+',
    operatorMult = '*',
    operatorDiv = '/',
    operatorPow = '^',
    operatorUnaryMinus = '!'
} Operator;

typedef struct {
    tokenType type;
    union {
        float number;
        char var[LEN];
        Operator op;
        char c;
    } data;
} token;

#endif