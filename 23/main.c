#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"



int main()
{
    Tree* tree = NULL; //сначала дерево пустое
    int value; //значение элемента дерева
    int parentValue; //значение отца
    int choose = 1; //переменная для выбора
    while (choose) {
        printMenu(); //выводим меню
        value = 0; //обнуляем значение
        parentValue = 0; //обнуляем значение
        scanf("%d", &choose); //считываем с клавиатуры выбор пользователя
        switch(choose) {
            case 0: //выход
                choose = 0;
            case 1: //создание узла
                printf("\nВведите значение элемента:\n");
                scanf("%d", &value);
                tree = newTree(value);
                break;
            case 2: //добавление вершины
                printf("\nВведите значение узла:\n");
                scanf("%d", &value);
                printf("\nВведите значение корня:\n");
                scanf("%d", &parentValue);
                addNodeToTree(tree, value, parentValue);
                break;
            case 3: //удаление вершины
                printf("\nВведите значение узла\n");
                scanf("%d", &value);
                deleteNode(tree, value);
                break;
            case 4: //подсчет уровня с макс значением вершин
                maxVertices(tree);
                attitude = 0;
                break;
            case 5: //вывод дерева
                printTree(tree->root, 0);
                break;
            default: //если нажали несуществующую опцию
                printf("Такого действия не существует!\n");
                break;
        }
    }
    return 0;
}
