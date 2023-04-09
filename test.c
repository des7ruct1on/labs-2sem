#include <stdio.h>
#include <stdlib.h>
typedef struct elementDeck elementDeck;
typedef struct deck deck;

struct elementDeck { //структура элемента из дека
    int value; // значение
    elementDeck* next; //указатель на след элемент
    elementDeck* prev; //указатель на предыдущий элемент
};

struct deck { //структура дека
    int size; //размер
    elementDeck* first; //первый элемент
    elementDeck* last; //последний элемент
};

void initialisation (deck* D) { //функция инициализации дека
    D->size = 0; //задаем нулевые параметры
    D->first = 0;
    D->last = 0;
}

void empty (deck* D) { //функция опустошения дека
    if (D->size == 0) {
        printf("Дек пуст!\n");
    }
    elementDeck* tmp = D->last;
    for (int i = D->size; i != 0; i--) {
        elementDeck* next = tmp->next;
        free(tmp);
        tmp = next;
    }
    D->last = NULL;
    D->first = NULL;
    D->size = 0;

}

void pushFront (deck* D, int value) { //добавление спереди
    elementDeck* tmp = (elementDeck*)malloc(sizeof(elementDeck)); //выделяем память на элемент
    tmp->value = value;//передаем ему значение из аргумента функции
    tmp->prev = NULL; //так как добавили спереди, то перед ним пусто
    tmp->next = D->first; // следующий для нашего элемента это бывший первый
    if (D->first) {
        D->first->prev = tmp; //теперь предыдущий для бывшего первого - новый
    }
    D->first = tmp; //теперь первый элемент в деке - новый элемент
    if (!D->last) { //если дек пуст
        D->last = tmp;
    }
    D->size++; //увеличиваем размер дека
}

void pushBack (deck* D, int value) { //добавление в конец
    elementDeck* tmp = (elementDeck*)malloc(sizeof(elementDeck)); //выделяем память
    tmp->value = value; //передаем значение
    tmp->next = NULL; //очевидно что след элемент - пустой
    tmp->prev = D->last; //указатель на предыдущий - последний элемент дека
    if (D->last) { //если есть последний
        D->last->next = tmp;
    }
    D->last = tmp; //последний - новый
    if (!D->first) { //если дек пуст
        D->first = tmp;
    }
    D->size++; //увеличиваем размер дека
}
int popFront (deck* D) {//взятие спереди
    if (D->size == 0) { //проверка на пустоту дека
        printf("Дек пустой!");
        return -1;
    }
    int value = D->first->value; //значение = значение первого
    if (D->first == D->last) { //если дек состоит из 1 элемента
        D->first = NULL; //обнуляем
        D->last = NULL;
    } else { //если дек состоит хотя бы из 2 элементов
        D->first = D->first->next;
        D->first->prev = NULL; //обнуляем
    }
    D->size--; //уменьшаем размер
    free(D->first);
    return value; //возвращаем значение
}

int popBack(deck* D) { //взятие с конца
    if (D->size == 0) { //проверка на пустоту дека
        printf("Дек пустой!");
        return -1;
    }
    int value = D->last->value; //значение = значение последнего
    if (D->first == D->last) { //если в деке ток 1 элемент
        D->first = NULL; //обнуляем
        D->last = NULL;
    } else { //если в деке хотя бы 2 элемента
        D->last = D->last->prev;
        D->last->next = NULL; //обнуляем
    }
    free(D->last);
    D->size--; //уменьшаем размер
    return value; //возвращаем значение
    
}

int top (deck* D) { //взятие значения элемента сверху дека
    if (D->size == 0) { //если пуст
        printf("Дек пустой!");
        return -1;
    } else {
        return D->first->value;
    }
}

int size (deck* D) { //функция, вычисляющая значение дека
    return D->size;
}

void printDeck (deck* D) { //вывод дека
    if (D->size == 0) { //если пустой
        printf("\n Дек пустой! \n");
    } else {
        printf("\n ( "); //скобка для вида
        elementDeck* tmp = D->first; //объявляем элемент, который будем выводить
        while (tmp) { //пока элемент существует в деке
            printf("%d ", tmp->value); //вывод
            tmp = tmp->next; //сдвигаем на следующий
        }
        printf(")\n"); //закрываем скобку
    }
}

void cat(deck* D1, deck* D2) { //конкатенация дека
    while (D2->size != 0) { //пока второй не пуст
        pushBack(D1, popFront(D2)); //добавляем элемент второго
    }
}

void append (deck* D1, deck* D2) {//добавление 1-ого в конец второго
    cat(D1, D2);
    for (int i = 0; i < size(D2); i++) {
        pushBack(D2, popFront(D2));
    }
}

void quickSort (deck* D) { //функция быстрой сортировки
    deck *D1 = malloc(sizeof(deck));
    deck *D2 = malloc(sizeof(deck));
    int value1, value2; //их значения
    if (D->size != 0) {//пока не пуст исходный
        initialisation(D1); //инициализируем оба дека
        initialisation(D2);
        value1 = popFront(D); //1 значение = взятый спереди
        while (D->size != 0) { //пока не пуст исходный
            if (top(D) < value1) { //если взятый сверху < взятого спереди
                pushBack(D1, popFront(D)); //добавляем в конец первого
            } else {
                pushBack(D2, popFront(D)); //добавляем в конец второго
            }
        }
        quickSort(D1); //рекурсивно повторяем для двух деков
        quickSort(D2);
        pushBack(D1, value1); //добавляем в конец 1-ого взятый спереди
        cat(D1, D2); //конкатенация первого и второго
        cat(D, D1); //конкатенация исходного и первого
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
    deck *D = malloc(sizeof(deck)); //исходный дек
    deck *D1 = malloc(sizeof(deck));
    deck *D2 = malloc(sizeof(deck));
    initialisation(D); //иниициализируем его
    int value; //его значение
    while (choose) { //пока выбираем
        printChoose();
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printf("Введите количество элементов ");
                scanf("%d", &numSize); //считываем размер дека
                initialisation(D1); //иниициализируем дек
                for (int i = 0;i < numSize / 2;i++) {
                    value = rand()%11; //заполняем рандомно
                    pushBack(D1, value);
                }
                initialisation(D2);
                for (int i = 0;i < numSize - numSize / 2;i++) {
                    value = rand()%11;
                    pushFront(D2, value);
                }
                cat(D1, D2); //конкатенация
                append(D, D1);
                empty(D1);
                free(D1);
                empty(D2);
                free(D2);
                printDeck(D); //вывод дека
                getchar();
                break;
            case 2:
                printDeck(D); //вывод дека
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
                quickSort(D); //быстрая сортировка
                printDeck(D); //вывод
                getchar();
                break;
            case 9:
                empty(D);
                initialisation(D); //инициализируем дек заново(опустошаем)
                
                break;
            case 10:
                printf("\nВведите размер дека: ");
                int numSize2;
                scanf("%d", &numSize2);
                initialisation(D1);
                printf("\nВведите значения элементов =>");
                for(int i = 0;i < numSize2; i++){
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
