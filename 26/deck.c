#include "deck.h"
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
