#include "tree.h"


int max(int a, int b) { //функция максимума
    return a > b ? a : b;
}

void dfs(node* tree, int level, int* levels) { //поиск в глубину
    if (tree == NULL) {
        return;
    }
    levels[level]++;
    dfs(tree->son, level + 1, levels);
    dfs(tree->brother, level, levels);
}

void maxVertices(Tree* tree) { //functin to calcucale the number of level with the max number of vertices
    int levels[1000] = {0};  // Maximum tree depth assumed to be 1000
    dfs(tree->root, 0, levels);
    for (int i = 0; i < 1000; i++) {
        if (levels[i] > maxSum) {
            maxSum = levels[i];
            maxLevel = i;
        }
    }
    printf("Уровень с максимальным количеством вершин: %d\n", maxLevel);
}


void printMenu() { //функция меню
    printf("\nВыберите действие и введите его номер\n");
    printf("0) Выход\n");
    printf("1) Создать корень дерева\n");
    printf("2) Добавить узел\n");
    printf("3) Удалить узел\n");
    printf("4) Вывести номер уровня с максимальным количеством элементов\n");
    printf("5) Распечатать дерево\n");
    
}
treeNode* newNode (int value, node* parent) { //функция создания нового узла
    node* nodeTemp;
    nodeTemp = (node*)malloc(sizeof(treeNode)); //выделяем память
    nodeTemp->value = value;//присваиваем значение
    nodeTemp->parent = parent;
    nodeTemp->son = NULL; //очевидно, что т.к это новая вершина, то сыновей и братьев у нее нет
    nodeTemp->brother = NULL;
    return nodeTemp;
}

Tree* newTree (int value) { //создаем корень
    Tree* tree = malloc(sizeof(Tree)); //выделяем память под дерево
    tree->root = newNode(value, NULL); //корнем дерева будет вершина со значением value и нулевым родителем
    return tree;
}
 
node* searchTree (node* tree, int val) { // поиск в дереве
    if (tree == NULL) {// если дерево пустое, то возвращаем значение tree
        return tree;
    }
    if (tree->value == val) {//нашли значение, которое искали
        return tree;
    }
    if (tree->son != NULL) {//если сын не нулевой, то рекурсивно вызываем функцию search tree от сына
        return searchTree(tree->son, val);
    }
    if (tree->son == NULL) {//сын нулевой, значит проверяем его брата
        return searchTree(tree->brother, val);
    }
    return tree;
}

void addNodeToTree(Tree* tree, int value, int parentValue) {//функция добавления вершины к узлу
    node* treeTemp = tree->root;
    treeTemp = searchTree(treeTemp, parentValue);
    if (treeTemp == NULL) {
        printf("Элемент со значением %d отсутсвует!", parentValue);
        return;
    }
    if (treeTemp->son == NULL) { //если сын пустой, то создаем вершину со значением value
        treeTemp->son = newNode(value, treeTemp);
    } else {
        treeTemp = treeTemp->son; //присваиваем значение сына нашему дереву
        while (treeTemp->brother != NULL) { //пока братья есть, двигаемся по ним ﬁ
            treeTemp = treeTemp->brother;
        }
        treeTemp->brother = newNode(value, treeTemp->parent);
    }
    
    
}

void deleteNode (Tree* tree, int value) { //функция удаления вершины
    node* nodeTemp = tree->root; //присваиваем значение корня дереву
    nodeTemp = searchTree(nodeTemp, value);//поиск в дереве по значение и нашему дереву от корня
    if (nodeTemp == NULL) {
        printf("Элемент со значением %d отсутсвует!", value);
        return;
    }
    if (nodeTemp->parent->son == nodeTemp) {
        nodeTemp->parent->son = nodeTemp->brother; // переход на брата
    } else {
        node* treeTemp = nodeTemp->parent->son;
        while (treeTemp != nodeTemp) {
            treeTemp = treeTemp->brother; //двигаемся по братьям
        }
        treeTemp->brother = treeTemp->brother;
        
    }
    free(nodeTemp); //высвобождаем память
}

void printTree(node* tree, int x) { //вывод дерева с парсированиемы
    if (tree == NULL) {
        return;
    }
    for (int i = 0;i < x;i++) {
        printf("\t");
    }
    printf("%d\n", tree->value);
    printTree(tree->son, x + 1);
    printTree(tree->brother, x);
}
