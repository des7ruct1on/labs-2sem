#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

int plusIndex(int i, int j) { //функция создания индекса элемента матрицы
    int checkLen;
    int len = 0;
    checkLen = j;
    while (checkLen) { //вычисляем длину правого индекса(столбца)
        checkLen /= 10;
        len++;
    }
    return i * pow(10, len) + j;
}

void printMatrix(vector* v, vector* vIndex, int size, int a, int b) { //функция вывода матрицы
    checkNullElements(v, vIndex);//проверяем на нулевые индексы
    int i = 1;
    int j = 1;
    int check = 0;
    int countNums = size * size; //количество элементов
    for (int k = 0; k < countNums; k++) {//цикл пока не вывели все элементы
        if (k % size == 0) {//если вывели всю строку, то печатаем перенос
            printf("\n");
        }
        if (loadVector(vIndex, check) == plusIndex(i, j)) {//если индекс перебора совпал с индексом не нулевого элемента
            printf("%d\t", loadVector(v, check));//выводим его
            check++;//увеличиваем счетчик вывода таких элементов
        }
        else {
            printf("0\t");//печатаем ноль, так как матрица разряженна
        }
        if (j == size) {//если столбцы закончилась, то увеличиваем счетчик строк
            j = 0;//обнуляем счетчик столбцов
            i++;
        }
        j++;//увеличиваем счетчик прохода по столбцу
    }
}

void matrochlen(vector* v, vector* vIndex, vector* E, vector* eIndex, int a, int b) {//функция матрочлена
    vector* resIndex = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* resValues = malloc(sizeof(vector));//выделяем память под вектор значений
    createVector(resIndex, sizeVector(vIndex) + sizeVector(eIndex));//создаем эти векторы
    createVector(resValues, sizeVector(vIndex) + sizeVector(eIndex));
    for (int i = 0; i < sizeVector(v); i++) {//меняем их значения в соотвествии с коэффицентами матрочлена
        int tmp = loadVector(v, i);
        writeVector(v, i, tmp * a);
    }
    for (int i = 0; i < sizeVector(E); i++) {//меняем их значения в соотвествии с коэффицентами матрочлена
        int tmp = loadVector(E, i);
        writeVector(E, i, tmp * b);
    }
    int i = 0;//параметры циклов
    int j = 0;
    int k = 0;
    while (i < sizeVector(eIndex) && j < sizeVector(vIndex)) {//цикл соединения 2 вектором в один отдельный
        if (loadVector(eIndex, i) < loadVector(vIndex, j)) {//если индекс единичной матрицы меньше матрицы М
            writeVector(resIndex, k, loadVector(eIndex, i));//записываем в массив индексов индекс из массива единичной
            writeVector(resValues, k, loadVector(E, i));//записываем соответствующее значение
            i++;
        }
        else if (loadVector(eIndex, i) > loadVector(vIndex, j)) {//противоположна ситуация первого if
            writeVector(resIndex, k, loadVector(vIndex, j));
            writeVector(resValues, k, loadVector(v, j));
            j++;
        }
        else { // если индексы совпали, то записываем сумму значений двух массивов, а в массив индексов идет индекс из массиво единичной
            writeVector(resIndex, k, loadVector(eIndex, i));
            writeVector(resValues, k, loadVector(E, i) + loadVector(v, j));
            i++;
            j++;
        }
        k++;
    }
    while (i < sizeVector(eIndex)) {//если массив индексов не единичной кончился, то нужно дописать оставшиеся 
        writeVector(resIndex, k, loadVector(eIndex, i));
        writeVector(resValues, k, loadVector(E, i));
        i++;
        k++;
    }
    while (j < sizeVector(vIndex)) {//если массив индексов единичной кончился, то дописываем оставшиеся из не единичной
        writeVector(resIndex, k, loadVector(vIndex, j));
        writeVector(resValues, k, loadVector(v, j));
        j++;
        k++;
    }
    k = 0;
    for (k = 0; k < sizeVector(resIndex); k++) {//если найден нулевой индекс, то соответствующее значение из вектора обнуляем
        if (loadVector(resIndex, k) == 0) {
            destroyElement(resIndex, resValues, k);
        }
    }
    printMatrix(resValues, resIndex, sizeVector(eIndex), a, b);//печатаем результат-матрицу
    destroyVector(resIndex);//освобождаем память
    destroyVector(resValues);
    free(resIndex);
    free(resValues);



}

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    vector* indexMatrix = malloc(sizeof(vector));//выделяем память под вектор индексов
    vector* valuesMatrix = malloc(sizeof(vector));//выделяем память под вектор значений
    int sizeRow;//количество строк
    int sizeColumn;//количество столбцов
    int a;//коэффицент a
    int b;//коэффицент b
    FILE* input;//файл, с которым будем работать
    printf("Вас приветствует программа по обработке разряженных матриц!\n");
    printf("Введите значение коэффицента a:\n");
    scanf("%d", &a);
    printf("Введите значение коэффицента b:\n");
    scanf("%d", &b);
    input = fopen(filename, "r");
    if (input == NULL) { // проверка на возможность открытия файла
        printf("Не удалось открыть файл!\n");
        return 1;
    }
    fscanf(input, "%d %d", &sizeRow, &sizeColumn);//считываем размер из файла
    if (sizeRow != sizeColumn) {
        printf("\nМатрица должна быть квадратной, иначе не выполнится задание!\n");
        return 1;
    }
    createVector(indexMatrix, 1);
    createVector(valuesMatrix, 1);
    int indexRow = 1;
    int indexColumn = 1;
    int indexVector = 0;
    while (!feof(input)) { //пока файл не пуст, считываем данные 
        int scanNum;
        fscanf(input, "%d", &scanNum);
        if (scanNum != 0) {
            writeVector(valuesMatrix, indexVector, scanNum);
            resizeVector(valuesMatrix, sizeVector(valuesMatrix) + 1);
            writeVector(indexMatrix, indexVector, plusIndex(indexColumn, indexRow));
            resizeVector(indexMatrix, sizeVector(indexMatrix) + 1);
            indexVector++;

        }
        indexRow++;
        if (indexRow == sizeRow + 1) {
            indexColumn++;
            indexRow = 1;
        }
    }
    resizeVector(indexMatrix, sizeVector(indexMatrix) - 1);
    resizeVector(valuesMatrix, sizeVector(valuesMatrix) - 1);
    fclose(input); //закрываем файл
    printf("\nИсходная матрица равна:\n");
    printMatrix(valuesMatrix, indexMatrix, sizeRow, a, b);
    vector* eIndex = malloc(sizeof(vector));
    vector* eValues = malloc(sizeof(vector));
    createVector(eIndex, sizeRow);
    createVector(eValues, sizeRow);
    int ind = 1;
    for (int i = 0; i < sizeRow; i++) {
        writeVector(eIndex, i, plusIndex(ind, ind));
        writeVector(eValues, i, 1);
        ind++;
    }
    printf("\n");
    printf("\nРезультата многочлена a * M + b * E:\n");
    if (a == 0 && b != 0) { // если a = 0, то выводим b * E
        for (int i = 0; i < sizeVector(eIndex); i++) {
            writeVector(eValues, i, loadVector(eValues, i) * b);
        }
        printMatrix(eValues, eIndex, sizeRow, a, b);
        destroyVector(eIndex);
        destroyVector(eValues);
        destroyVector(indexMatrix);
        destroyVector(valuesMatrix);
        free(indexMatrix);
        free(valuesMatrix);
        free(eIndex);
        free(eValues);
        return 0;
    }
    else if (b == 0 && a != 0) { //если b = 0, то выводим a * M
        for (int i = 0; i < sizeVector(indexMatrix); i++) {
            writeVector(valuesMatrix, i, loadVector(valuesMatrix, i) * a);
        }
        printMatrix(valuesMatrix, indexMatrix, sizeRow, a, b);
        destroyVector(eIndex);
        destroyVector(eValues);
        destroyVector(indexMatrix);
        destroyVector(valuesMatrix);
        free(indexMatrix);
        free(valuesMatrix);
        free(eIndex);
        free(eValues);
        return 0;
    }
    else { 
        matrochlen(valuesMatrix, indexMatrix, eValues, eIndex, a, b);
        destroyVector(eIndex);
        destroyVector(eValues);
        destroyVector(indexMatrix);
        destroyVector(valuesMatrix);
    }
    free(indexMatrix);
    free(valuesMatrix);
    free(eIndex);
    free(eValues);

    return 0;
}

