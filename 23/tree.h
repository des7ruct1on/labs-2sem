#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode { //структура вершины
    int value; //значение
    struct treeNode *parent; //указатель на родителя
    struct treeNode *son; //указатель на сына
    struct treeNode *brother; //указатель на брата
} treeNode;

typedef struct treeNode node;

typedef struct Tree { //структура узла
    node *root;
} Tree;

void maxVertices(Tree* tree);

treeNode* newNode (int value, node* parent);

Tree* newTree (int value);

node* searchTree (node* tree, int val);

void addNodeToTree(Tree* tree, int value, int parentValue);

void deleteNode (Tree* tree, int value);

void clearNode(node* tree);

void clearTree(Tree* tree);

void maxVertices (Tree* root);

void printLevel(treeNode* root, int level);

void printTree(node* tree, int x);

void dfs(node* tree, int level, int** levels_ptr, int* size);
#endif
