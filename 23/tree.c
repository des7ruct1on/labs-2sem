#include "tree.h"

void dfs(node* tree, int level, int** levels_ptr, int* size) { // поиск в глубину
    if (tree == NULL) { // если дерево пустое
        return;
    }
    if (level >= *size) { //динамическое выделение памяти под массив
        *size = level + 1;
        *levels_ptr = realloc(*levels_ptr, *size * sizeof(int));
        (*levels_ptr)[level] = 0;
    }
    (*levels_ptr)[level]++;
    dfs(tree->son, level + 1, levels_ptr, size); // рекурсия
    dfs(tree->brother, level, levels_ptr, size);
}

void maxVertices(Tree* tree) { // функция поиска уровня с макс количеством вершин
    int maxSum = 0; //макс сумма
    int maxLevel = 0; //максимальный уровень
    int size = 0; //размер массива
    int* levels = NULL; //создаем массив глубины
    dfs(tree->root, 0, &levels, &size);
    for (int i = 0; i < size; i++) {
        if (levels[i] > maxSum) { // поиск максимума
            maxSum = levels[i];
            maxLevel = i;
        }
    }
    printf("Уровень с максимальным количеством вершин: %d\n", maxLevel);
    free(levels); // очищаем массив
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
 
node* searchTree(node* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->value == value) {
        return tree;
    }
    node* found = searchTree(tree->son, value);
    if (found == NULL) {
        found = searchTree(tree->brother, value);
    }
    return found;
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
        while (treeTemp->brother != nodeTemp) { // пока не найдем брата удаляемого узла
            treeTemp = treeTemp->brother;
        }
        treeTemp->brother = nodeTemp->brother; // убираем узел из списка братьев
    }
    if (nodeTemp->brother != NULL) {
        nodeTemp->brother->parent = nodeTemp->parent; // обновляем указатель на родителя у брата
    }
    free(nodeTemp); // очищаем удаляемый узел
}
void clearNode(node* tree) { // функция очистки вершины
    if (tree == NULL) { // проверяем, что вершина не пустая
        return;
    }
    clearNode(tree->son); // очищаем сыновей
    clearNode(tree->brother); // очищаем братьев
    free(tree); // освобождаем память
}
void clearTree(Tree* tree) { // функция очистки дерева
    if (tree == NULL) { // проверяем, что дерево не пустое
        return;
    }
    if (tree->root != NULL) { // проверяем, что корень дерева не пустой
        clearNode(tree->root); // очищаем корень
        tree->root = NULL; // присваиваем корню дерева значение NULL
    }
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
