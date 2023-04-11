#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "deck.h"

void printChoose() { //вывод выбора действий
    printf("\nВыберите действие:\n");
    printf("0)Выход\n");
    printf("1)Создать рандомный дек\n");
    printf("2)Вывести содержимое дека\n");
    printf("3)Узнать размер дека\n");
    printf("4)Вставить элемент в начало\n");
    printf("5)Вставить элемент в конец\n");
    printf("6)Удалить первый элемент\n");
    printf("7)Удалить последний элемент\n");
    printf("8)Сортировка\n");
    printf("9)Опустошить дек\n");
    printf("10)Конкатенация двух деков\n");
}

void quickSort(deck *D) { //функция быстрой сортировки
    deck *D1 = malloc(sizeof(deck));
    deck *D2 = malloc(sizeof(deck));
    initDeck(D1);
    initDeck(D2);
    int value; //их значения
    if (!empty(D)) {//пока не пуст исходный

        value = popFront(D); //1 значение = взятый спереди
        while (!empty(D)) { //пока не пуст исходный
            if (topFront(D) < value) { //если взятый сверху < взятого спереди
                pushBack(D1, popFront(D)); //добавляем в конец первого
            } else {
                pushBack(D2, popFront(D)); //добавляем в конец второго
            }
        }
        quickSort(D1); //рекурсивно повторяем для двух деков
        quickSort(D2);
        pushBack(D1, value); //добавляем в конец 1-ого взятый спереди
        cat(D1, D2); //конкатенация первого и второго
        cat(D, D1); //конкатенация исходного и первого
    }
    deleteDeck(D1);
    deleteDeck(D2);
}

int main(int argc, const char *argv[]) {
    int choose = 1; // переменная выбора
    int numSize; // размер дека
    deck *D = malloc(sizeof(deck)); // выделяем память под дек
    deck *D1 = malloc(sizeof(deck));
    initDeck(D);
    int value; //значение дека
    while (choose) {
        printChoose();
        scanf("%d", &choose);
        switch (choose) {
            case 0:
                deleteDeck(D);
                deleteDeck(D1);
                break;
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер дека
                for (int i = 0; i < numSize; i++) {
                    value = rand() % 11;
                    pushFront(D, value);
                }
                printDeck(D);
                getchar();
                break;
            case 2:
                printDeck(D);
                getchar();
                break;
            case 3:
                numSize = size(D); //присваиваем размер дека
                printf("\nРазмер дека: %d", numSize);
                break;
            case 4:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushFront(D, value); //добавляем введенное значение спереди
                break;
            case 5:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushBack(D, value); //добавляем сзади
                break;
            case 6:
                value = popFront(D); //взятие первого элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 7:
                value = popBack(D); //взятие последнего элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 8:
                quickSort(D);
                printDeck(D);
                getchar();
                break;
            case 9:
                deleteDeck(D);
                initDeck(D);
                break;
            case 10:
                printf("\nВведите размер дека: ");
                int numSize2;
                scanf("%d", &numSize2);
                initDeck(D1);
                printf("\nВведите значения элементов =>");
                for (int i = 0; i < numSize2; i++) {
                    scanf("%d", &value);
                    pushBack(D1, value);
                }
                cat(D, D1); //конкатенация деков
                printDeck(D); //вывод
                getchar();
                break;
        }
    }
    return 0;
}