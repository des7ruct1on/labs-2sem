#include "tree.h"
#include "symbol.h"

bool builtTree(treeNode** tree, stack* rev) {
    if(stackEmpty(rev)) {
        return false;
    }
    symbol t = stackPop(rev);
    (*tree) = (treeNode*)malloc(sizeof(treeNode));
    (*tree)->t = t;
    bool res = true;
    if(t.type == symbOperator) {
        if(t.data.op == operatorUnaryMinus) {
            (*tree)->left = NULL;
            res = res && builtTree(&((*tree)->right), rev);
        } else {
            res = res && builtTree(&((*tree)->right), rev);
            res = res && builtTree(&((*tree)->left), rev);
        }
    }
    return true;
}

void printTree(treeNode* tree, int lev) {
    if(tree->t.type == symbOperator) {
        printTree(tree->right, lev + 1);
    }
    for (int i = 0; i < lev; i++) {
        printf("\t");
    }
    switch (tree->t.type)
    {
        case symbNum:
            printf("%.2lf\n", tree->t.data.number);
            break;
        case symbVar:
            printf("%s\n", tree->t.data.var);
            break;
        case symbOperator:
            if (tree->t.data.op == operatorUnaryMinus) {
                printf("-\n");
                printTree(tree->right, lev + 1);
            } else {
                printf("%c\n", operatorToChar(tree->t.data.op));
            }
            break;
        default:
            fprintf(stderr, "Символ уже есть в дереве\n");
            return;
    }
    if(tree->t.type == symbOperator) {
        printTree(tree->left, lev + 1);
    }
}

void printExpr(treeNode* tree) {
    switch(tree->t.type) {
        case symbNum:
            printf("%.2lf", tree->t.data.number);
            break;
        case symbVar:
            printf("%s", tree->t.data.var);
            break;
        case symbOperator:
            if(tree->t.data.op == operatorUnaryMinus) {
                printf("-");
                printExpr(tree->right);
            } else {
                if (tree->left->t.type == symbOperator && opPriority(tree->t.data.op) > opPriority(tree->left->t.data.op)) {
                    printf("(");
                    printExpr(tree->left);
                    printf(")");
                } else {
                    printExpr(tree->left);
                }
                printf("%c", operatorToChar(tree->t.data.op));
                if(tree->left->t.type == symbOperator && opPriority(tree->t.data.op) > opPriority(tree->right->t.data.op)) {
                    printf("(");
                    printExpr(tree->right);
                    printf(")");
                } else {
                    printExpr(tree->right);
                }
                break;
                
            }
        default:
            fprintf(stderr, "Символ уже есть!");
            return;

    }
}

