#include <stdio.h>
#include <stdlib.h>
#include "deck.h"

void quickSort (deck* D) { //функция быстрой сортировки
    deck D1, D2; //два дека
    int value1, value2; //их значения
    if (!empty(D)) {//пока не пуст исходный
        initialisation(&D1); //инициализируем оба дека
        initialisation(&D2);
        value1 = popFront(D); //1 значение = взятый спереди
        while (!empty(D)) { //пока не пуст исходный
            if (top(D) < value1) { //если взятый сверху < взятого спереди
                pushBack(&D1, popFront(D)); //добавляем в конец первого
            } else {
                pushBack(&D2, popFront(D)); //добавляем в конец второго
            }
        }
        quickSort(&D1); //рекурсивно повторяем для двух деков
        quickSort(&D2);
        pushBack(&D1, value1); //добавляем в конец 1-ого взятый спереди
        cat(&D1, &D2); //конкатенация первого и второго
        cat(D, &D1); //конкатенация исходного и первого
        free(D1);
        free(D2);
    }
}

void printChoose () { //вывод выбора действий
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

int main(int argc, const char * argv[]) {
    int choose = 1; //переменная выбора
    int numSize; //размер дека
    deck D; //исходный дек
    initialisation(&D); //иниициализируем его
    int value; //его значение
    deck D1, D2; //объявляем 2 дека
    while (choose) { //пока выбираем
        printChoose();
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер дека
                initialisation(&D1); //иниициализируем дек
                for (int i = 0;i < numSize / 2;i++) {
                    value = rand()%11; //заполняем рандомно
                    pushBack(&D1, value);
                }
                initialisation(&D2);
                for (int i = 0;i < numSize - numSize / 2;i++) {
                    value = rand()%11;
                    pushFront(&D2, value);
                }
                cat(&D1, &D2); //конкатенация
                append(&D, &D1);
                printDeck(&D); //вывод дека
                getchar();
                break;
            case 2:
                printDeck(&D); //вывод дека
                getchar();
                break;
            case 3:
                numSize = size(&D); //присваиваем размер дека
                printf("\nРазмер дека: %d", numSize);
                break;
            case 4:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushFront(&D, value); //добавляем введенное значение спереди
                break;
            case 5:
                printf("\nВведите значение элемента: ");
                scanf("%d", &value);
                pushBack(&D, value); //добавляем сзади
                break;
            case 6:
                value = popFront(&D); //взятие первого элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 7:
                value = popBack(&D); //взятие последнего элемента и его удаление
                printf("\nЭлемент =%d удален\n", value);
                break;
            case 8:
                quickSort(&D); //быстрая сортировка
                printDeck(&D); //вывод
                getchar();
                break;
            case 9:
                initialisation(&D); //инициализируем дек заново(опустошаем)
                break;
            case 10:
                printf("\nВведите размер дека: ");
                int numSize2;
                scanf("%d", &numSize2);
                initialisation(&D1);
                printf("\nВведите значения элементов =>");
                for(int i = 0;i < numSize2; i++){
                    scanf("%d", &value);
                    pushBack(&D1, value);
                }
                cat(&D, &D1); //конкатенация деков
                printDeck(&D); //вывод
                getchar();
                break;
        }
    }
    return 0;
}
