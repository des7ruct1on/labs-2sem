#ifndef tree_h
#define tree_h
#include <stdlib.h>
#include <stdbool.h>
#include "symbol.h"
#include "stack.h"
typedef struct treeNode {
    symbol t;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

void printTree(treeNode* tree, int lev);
bool builtTree(treeNode** tree, stack* rev);
void printExpr(treeNode* tree);
#endif