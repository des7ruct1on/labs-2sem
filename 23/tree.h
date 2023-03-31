#ifndef tree_h
#define tree_h

#include <stdio.h>
#include <stdlib.h>

int sum = 0; //глобальные переменные для удобства
int maxSum = 0;
int maxLevel = 0;
int attitude = 0;

int max(int a, int b);

void printMenu();

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

int height(treeNode* tree);

void maxVertices(Tree* tree);

treeNode* newNode (int value, node* parent);

Tree* newTree (int value);

node* searchTree (node* tree, int val);

void addNodeToTree(Tree* tree, int value, int parentValue);

void deleteNode (Tree* tree, int value);

void printTree(node* tree, int x);

void maxVertices (Tree* root);

void printLevel(treeNode* root, int level);

void dfs(node* tree, int level, int* levels);
#endif
