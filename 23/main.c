#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"

void printMenu() { //функция меню
    printf("\nВыберите действие и введите его номер\n");
    printf("0) Выход\n");
    printf("1) Создать корень дерева\n");
    printf("2) Добавить узел\n");
    printf("3) Удалить узел\n");
    printf("4) Вывести номер уровня с максимальным количеством элементов\n");
    printf("5) Распечатать дерево\n");
    
}

int max(int a, int b) { //функция максимума
    return a > b ? a : b;
}


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
                clearTree(tree);
                free(tree);
                break;
            case 1: //создание узла
                if (tree != NULL) {
                    clearTree(tree);
                    free(tree);
                }
                printf("\nВведите значение элемента:\n");
                scanf("%d", &value);
                tree = newTree(value);
                break;
            case 2: //добавление вершины
                if (tree == NULL) {
			        printf("Ошибка! Корень не создан\t");
			        break;
		        }
                printf("\nВведите значение узла:\n");
                scanf("%d", &value);
                printf("\nВведите значение вершины:\n");
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

