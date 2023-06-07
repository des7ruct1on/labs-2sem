#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define MAX_EXPRESSION_LENGTH 100

void next_symbol(Symbol* symbol, char input[]) {
    static int index = 0;
    char c = input[index];
    static SymbolType prev = symb_NONE;
    if (c == '\0') {  // проверяем на конец строки
        symbol->type = symb_NONE;
        prev = symb_NONE;
        return;
    }

    if (isdigit(c)) {
        symbol->type = symb_NUMBER;
        symbol->data.number = c - '0';
        index++;  // двигаемся дальше по строке

        // Считываем все цифры числа
        while (isdigit(input[index])) {
            symbol->data.number = symbol->data.number * 10 + (input[index] - '0');
            index++;
        }
    } else if (isOperator(c)) {
        symbol->type = symb_OP;
        symbol->data.op = c;
        index++;  // двигаемся дальше по строке
    } else if (isalpha(c)) {
        symbol->type = symb_VAR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == '(') {
        symbol->type = symb_LEFT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == ')') {
        symbol->type = symb_RIGHT_BR;
        symbol->data.c = c;
        index++;  // двигаемся дальше по строке
    } else if (c == '-') {
        symbol->type = symb_OP;
        if (prev == symb_OP || prev == symb_NONE) {
            symbol->data.op = OP_UNARY_MINUS;
        } else {
            symbol->data.op = OP_MINUS;
        }
        index++;  // двигаемся дальше по строке
    } else {
        symbol->type = symb_NONE;
        index++;  // двигаемся дальше по строке
    }
    prev = symbol->type;
}

void infixToPostfix(char exp[], node** expression) {
    stack* s = malloc(sizeof(stack));
    initStack(s);

    Symbol t;
    next_symbol(&t, exp);

    while (t.type != symb_NONE) {
        switch (t.type) {
            case symb_NONE:
                fprintf(stderr, "Ошибка! символ %c не распознан\n", t.data.c);
                return;

            case symb_OP:
                for (;;) {
                    if (stackEmpty(s))
                        break;

                    Symbol top = stackTopSymbol(s);

                    if (top.type != symb_OP)
                        break;

                    if ((op_assoc(t.data.op) == ASSOC_LEFT && getPriority(t.data.op) <= getPriority(top.data.op)) ||
                        (op_assoc(t.data.op) == ASSOC_RIGHT && getPriority(t.data.op) < getPriority(top.data.op))) {
                        pushBack(expression, top);
                        stackPopSymbol(s);
                    } else {
                        break;
                    }
                }
                stackPushSymbol(s, t);
                break;

            case symb_NUMBER:
            case symb_VAR:
                pushBack(expression, t);
                break;

            case symb_LEFT_BR:
                stackPushSymbol(s, t);
                break;

            case symb_RIGHT_BR:
                while (!stackEmpty(s) && stackTopSymbol(s).type != symb_LEFT_BR) {
                    pushBack(expression, stackPopSymbol(s));
                }

                if (stackEmpty(s)) {
                    fprintf(stderr, "Ошибка: пропущена скобка\n");
                    return;
                }

                stackPopSymbol(s);
                break;
        }

        next_symbol(&t, exp);
    }

    while (!stackEmpty(s)) {
        if (stackTopSymbol(s).type == symb_LEFT_BR) {
            fprintf(stderr, "Ошибка: пропущена скобка\n");
            return;
        }

        pushBack(expression, stackPopSymbol(s));
    }

    stackDestroy(s);
}

Tree* postfixToTree(node* postfix) {
    stack* s = malloc(sizeof(stack));
    initStack(s);
    for(node* current = postfix; current != NULL; current = current->next) {
        Symbol c = current->data;
        if (c.type != symb_OP) {
            Tree* tmp = createTree(c);
            stackPushTree(s, tmp);
        } else if (c.type == symb_OP) {
            Tree* right = stackPopTree(s);
            Tree* left = stackPopTree(s);
            Tree* op = createTree(c);
            op->left = left;
            op->right = right;
            stackPushTree(s, op);
        }
    }
    Tree* res = stackPopTree(s);
    stackDestroy(s);
    return res;
}

void simplifyFraction(Tree* node) {
    if (node == NULL)
        return;

    simplifyFraction(node->left);// рекурсовно упрощаем числитель
    simplifyFraction(node->right);//упрощаем знаменатель

    if (node->value.type == symb_OP && node->value.data.op == OP_DIVIDE) {
        Tree* numerator = node->left;
        Tree* denominator = node->right;
        if (denominator->value.data.op == OP_DIVIDE && numerator->value.data.op != OP_DIVIDE) { //обрабатываем случай деления справа
            node->value.data.op = OP_MULTIPLY;
            node->right = denominator->right;
            node->left = denominator;
            denominator->right = denominator->left;
            denominator->left = numerator;
        } else if (numerator->value.data.op == OP_DIVIDE && denominator->value.data.op != OP_DIVIDE) { //обрабатываем случай деления слева
            node->right = numerator;
            node->left = denominator;
            node->left = numerator->left;
            numerator->left = denominator;
            node->right->value.data.op = OP_MULTIPLY;
        } else if (denominator->value.data.op == OP_DIVIDE && numerator->value.data.op == OP_DIVIDE) { //обрабатываем общий случай
            numerator->value.data.op = OP_MULTIPLY;
            denominator->value.data.op = OP_MULTIPLY;
            Tree* rightRight = denominator->right;
            Tree* leftRight = numerator->right;
            denominator->right = leftRight;
            numerator->right = rightRight;
        }

    }
}




void treeToPostfix(Tree* node, char postfixExp[]) {
    if (node == NULL)
        return;

    treeToPostfix(node->left, postfixExp);
    treeToPostfix(node->right, postfixExp);

    if (node->value.type == symb_NUMBER || node->value.type == symb_VAR) {
        char str[2] = {node->value.data.c, '\0'};
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    } else if (node->value.type == symb_OP) {
        char str[2] = {node->value.data.op, '\0'};
        strcat(postfixExp, " ");
        strcat(postfixExp, str);
        strcat(postfixExp, " ");
    }
}

void treeToExpresion(Tree* tree) {
    switch (tree->value.type) {
        case symb_NUMBER:
            printf("%.2lf", tree->value.data.number);
            break;
        case symb_VAR:
            printf("%c", tree->value.data.c);
            break;
        case symb_OP:
            if (tree->value.data.op == OP_UNARY_MINUS) {
                printf("-");
                treeToExpresion(tree->right);
            } else {
                bool addParenthesesLeft = (tree->left->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->left->value.data.op));
                bool addParenthesesRight = (tree->right->value.type == symb_OP && getPriority(tree->value.data.op) > getPriority(tree->right->value.data.op));

                if (tree->value.data.op == OP_DIVIDE && !addParenthesesLeft && !addParenthesesRight) {
                    // В случае деления добавляем скобки только для нумератора и знаменателя, если они сами являются операторами
                    addParenthesesLeft = (tree->left->value.type == symb_OP);
                    addParenthesesRight = (tree->right->value.type == symb_OP);
                }

                if (addParenthesesLeft) {
                    printf("(");
                }
                treeToExpresion(tree->left);
                if (addParenthesesLeft) {
                    printf(")");
                }

                printf("%c", oppToChar(tree->value.data.op));

                if (addParenthesesRight) {
                    printf("(");
                }
                treeToExpresion(tree->right);
                if (addParenthesesRight) {
                    printf(")");
                }
            }
            break;
        default:
            fprintf(stderr, "Ошибка, такого символа нет");
            return;
    }
}



int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    stack* s1 = malloc(sizeof(stack));
    initStack(s1);
    char exp[MAX_EXPRESSION_LENGTH];
    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Не удалось прочитать данные из файла.\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    node* expression = NULL;
    infixToPostfix(exp, &expression);
    Tree* tree = postfixToTree(expression);
    destroy(expression);
    printTree(tree, 0);
    printf("Упрощенное дерево выражений:\n");
    simplifyFraction(tree);
    printTree(tree, 0);
    //char postfixExp[MAX_EXPRESSION_LENGTH] = "";
    //treeToPostfix(tree, postfixExp);
    //printf("Постфиксное выражение: %s\n", postfixExp);
    treeToExpresion(tree);
    clearTree(tree);
    stackDestroy(s1);
    return 0;
}