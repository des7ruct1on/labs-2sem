#include "list.h"

void pushFront(Node** head, char data) { //функция добавления спереди
    Node* newNode = (Node*)malloc(sizeof(Node)); //выделяем память
    newNode->data = data; //присваиваем значение литеры
    if (*head == NULL) { //если "голова" пустая
        *head = newNode; //добавленный элемент - голова списка
        newNode->prev = newNode->next = newNode; //ссылка на самого себя
    } else { // иначе
        Node* last = (*head)->prev; 
        newNode->prev = last; //предыдущий нового элемента - предыдущий у головы
        newNode->next = *head; //некст - head
        (*head)->prev = newNode; //связываем голову и новый элемент сзади
        last->next = newNode; //связываем некст и новый
        *head = newNode;
    }
}

void pushIndex(Node** head, char data, int k) {
    int size = sizeList(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));//выделяем память
    newNode->data = data;//присваиваем значение литеры
    Node* current = *head;
    if (*head == NULL && k == 0) {
        *head = newNode;
        current = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else if (k == 0) {
        Node* last = current->prev;
        last->next = newNode;
        newNode->prev = last;
        current->prev = newNode;
        newNode->next = current;
        *head = newNode;
    } else {    
        for (int i = 0; i < k; i++) { // движемся до k
            current = current->next;
        }
        Node* left = current->prev;
        left->next = newNode;
        newNode->prev = left;
        current->prev = newNode;
        newNode->next = current;
    }
}

void deleteIndex(Node** head, int k) {
    int size = sizeList(*head);
    if (k > size || k < 0) {
        printf("Выход за границы списка!\n");
        return;
    }
    if(*head == NULL) {
        return;
    }
    if (k == 0) {
        if ((*head)->next == *head) { // если в списке 1 элемент
            free(*head);
            *head = NULL;
        } else {
            Node* last = (*head)->prev;
            Node* second = (*head)->next;
            last->next = second;
            second->prev = last;
            free(*head);
            *head = second;
        }
    } else {
        Node* current = *head;
        for(int i = 0; i < k; i++) {
            current = current->next;
        }
        Node* left = current->prev;
        Node* right = current->next;
        left->next = right;
        right->prev = left;
        free(current);
    }
}

void pushBack(Node** head, char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));//выделяем память
    newNode->data = data;//присваиваем значение литеры
    if (*head == NULL) {//если "голова" пустая
        *head = newNode;//добавленный элемент - голова списка
        newNode->prev = newNode->next = newNode;//ссылка на самого себя
    } else {// иначе (инверсия pushFront)
        Node* last = (*head)->prev;
        newNode->prev = last;
        newNode->next = *head;
        (*head)->prev = newNode;
        last->next = newNode;
    }
}

void deleteFront(Node** head) { //функция удаления спереди
    if (*head == NULL) { 
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) { //если только один элемент в списке
        free(*head);
        *head = NULL;
    } else {
        Node* last = (*head)->prev; //заопминаем предыдуший и некст
        Node* second = (*head)->next;
        last->next = second; //вычленяем голову и связываем запомнившиеся элементы
        second->prev = last;
        free(*head);
        *head = second; //нвоая голова
    }
}

void deleteBack(Node** head) { //функция удаления сзади
    if (*head == NULL) {
        printf("Список пуст!\n");
    } else if ((*head)->next == *head) { //если только один элемент в списке
        free(*head);
        *head = NULL;
    }else {  // инверсия функции удаления спереди
        Node* last = (*head)->prev;
        Node* second = last->prev;
        second->next = *head;
        (*head)->prev = second;
        free(last);
    }
}

void destroy(Node* head) { //функция очистки 
    if (head == NULL) {
        return;
    } else {
        Node* current = head; //начинаем с головы
        do {
            Node* tmp = current->next; //пока не вернулись к голове, движемся 
            free(current); //освобождаем 
            current = tmp;
        } while (current != head);
    }
}
void swap(Node** head, int k) { //функция варианта (swap k-1 элемент с k+1)
    int size = sizeList(*head);
    if (*head == NULL) {
        printf("Список пуст!\n");
    } else if (k < 0 || k >= size) { //проверка на применимость k
        printf("Индекс k должен быть в диапазоне от 0 до %d!\n", size-1);
    } else { //если все ок
        Node* current = *head;
        for (int i = 0; i < k; i++) { // движемся до k
            current = current->next;
        }
        Node* swapLeft = current->prev; //запоминаем предыдущий
        Node* swapRight = current->next;//запоминаем следующий
        Node* swapLeftPrev = current->prev->prev;//запоминаем перед предыдущим
        Node* swapRightNext = current->next->next;//аналогично некст у следующего
        if (swapLeft == *head) { //если левый сосед - голова
            current->prev = swapRight; //swap
            *head = swapRight;
            current->next = swapLeft; //swap
        } else if(swapRight == *head) { //если правый сосед - голова
            current->prev = swapRight; //swap
            current->next = swapLeft; //swap
            *head = swapLeft;
        } else { 
            current->prev = swapRight; //swap
            current->next = swapLeft; //swap
        }
        if (size == 3) {
            swapLeft->next = swapRight;
            swapLeft->prev = current;
            swapRight->next = current;
            swapRight->prev = swapLeft;
            swapRightNext = swapLeft->next;
            swapLeftPrev = swapRight->prev;
        } else {
            swapLeftPrev->next = swapRight; //далее просто связываем все элементы
            swapRightNext->prev = swapLeft;
            swapLeft->prev = current;
            swapLeft->next = swapRightNext;
            swapRight->prev = swapLeftPrev;
            swapRight->next = current;
        }
    }
}



void printList(Node* head) { //функция вывода списка
    if (head == NULL) {
        printf("Список пуст!\n");
    } else {
        Node* current = head;
        printf("("); //печатаем скобку для красоты
        do {
            printf("%c", current->data); //двигаемся пока не дошли до головы
            current = current->next;
            if(current != head) { //печатаем запятую
                printf(", ");
            }
        } while (current != head);
        printf(")");
    }
}

int sizeList(Node* head) { //функция вывода размера списка
    if (head == NULL) {
        return 0;
    } else {
        Node* current = head;
        int counter = 0;
        do { //пока не дошли до головы увеличиваем счетчик
            counter++;
            current = current->next;
        } while (current != head);
        return counter;
    }
}