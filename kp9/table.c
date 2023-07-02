#include "table.h"

void createVector(vector* v, int size) {
    v->size = size;
    v->data = (value*)malloc(size * sizeof(value));
    for (int i = 0; i < size; i++) {
        strcpy(v->data[i].key, "");
        strcpy(v->data[i].string, "");
    }
}


bool empty(vector* v) { //функция проверки на пустоту
    return v->size == 0;
}

int sizeVector(vector* v) {//функция возвращения размера вектора
    return v->size;
}

value loadVector(vector* v, int i) {//функция вывода элемента вектора
    value emptyValue;
    strcpy(emptyValue.key, ""); //нулевые значения
    strcpy(emptyValue.string, "");
    
    if (i >= 0 && i < v->size) {
        return v->data[i];
    } else {
        return emptyValue;
    }
}

void writeVector(vector* v, int i, value val) {
    if (i >= 0 && i < v->size) {
        v->data[i] = val;
    }
}

void resizeVector(vector* v, int size) { //функция изменения размера вектора
    value* new_values = (value*)realloc(v->data, size * sizeof(value));
    v->data = new_values;
    v->size = size;

    if (v->size > size) {
        for (int i = size; i < v->size; i++) {
            strcpy(v->data[i].key, "");
            strcpy(v->data[i].string, "");
        }
    }
}

void destroyVector(vector* v) {//функция очистки вектора 
    v->size = 0;
    free(v->data);
    v->data = NULL;
}

void printTable(vector* v) { //функция вывода таблицы
    int size = sizeVector(v);
    printf("|============================================|\n");
    printf("|  Ключ  | Значение                          |\n");
    printf("|============================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(v, i);
        printf("| %6s | %-41s \n", tmp.key, tmp.string);
    }
    printf("|============================================|\n");
}

int compareKeys(value x, value y) {
    return strcmp(x.key, y.key);
}

void swap(value* x, value* y) { //функция свапа указателей 
    value temp = *x;
    *x = *y;
    *y = temp;
}

void sortShake(vector* v) { //функция шейк-сортировки
    int left = 0; 
    int right = v->size - 1;
    bool swapped = true;

    while (left < right && swapped) {
        swapped = false;

        for (int i = left; i < right; i++) {
            if (compareKeys(v->data[i], v->data[i + 1]) > 0) {
                swap(&v->data[i], &v->data[i + 1]);
                swapped = true;
            }
        }

        right--;

        for (int i = right; i > left; i--) {
            if (compareKeys(v->data[i - 1], v->data[i]) > 0) {
                swap(&v->data[i - 1], &v->data[i]);
                swapped = true;
            }
        }

        left++;
    }
}

value binarySearch(vector* table, char key[6]) { //функция бинарного поиска по ключу
    int left = 0;
    int right = sizeVector(table) - 1;
    int middle;
    value def = { "", "" }; //если ничено не найдем, то вернем пустой объект

    while (left <= right) {
        middle = (left + right) / 2;

        if (strcmp(key, table->data[middle].key) < 0) {
            right = middle - 1;
        } else if (strcmp(key, table->data[middle].key) > 0) {
            left = middle + 1;
        } else {
            return table->data[middle];
        }
    }

    return def;
}

bool checkSortTable(vector* table) { // функция проверки на отсортированность таблицы
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = loadVector(table, i);
        value b = loadVector(table, i + 1);

        if (compareKeys(a, b) > 0) { //если нарушен порядок
            return false;
        }
    }

    return true;
}

bool checkSortTableDescending(vector* table) {// функция проверки на убывание(обратные порядок)
    int size = sizeVector(table);
    for (int i = 0; i < size - 1; i++) {
        value a = loadVector(table, i);
        value b = loadVector(table, i + 1);

        if (compareKeys(a, b) < 0) { // если нарушен порядок
            return false;
        }
    }

    return true;
}

void vectorReverse(vector* a, vector* b) { //функция записи реверс вектора
    int size = sizeVector(a);
    int pos = 0;
    for(int i = size - 1; i >= 0; i--) {
        value tmp = loadVector(a, i);
        writeVector(b, pos, tmp);
        pos++;
    }
}