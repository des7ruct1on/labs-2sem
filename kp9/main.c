#include <math.h>
#include <ctype.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "table.h"

void printMenu() {
    printf("\nВыберите дейтсвие:\n");
    printf("0)Выход\n");
    printf("1)Отсортировать таблицу\n");
    printf("2)Найти строку по ключу\n");
    printf("3)Распечатать таблицу\n");
    printf("4)Перезаписать файл\n");
}

void rewriteFile(const char* filename, vector* table) { //функция перезаписи файла
    FILE* file = fopen(filename, "w"); //открываем файл с разрешением на запись
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    int size = sizeVector(table);
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(table, i); //берем каждый элемент вектора
        fprintf(file, "%s %s\n", tmp.key, tmp.string); //записываем в файл
    }

    fclose(file);
}

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Используйте: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    vector* table = malloc(sizeof(vector)); //выделяем память под вектор
    createVector(table, 0);

    char line[STRSIZE]; //линия из файла
    while (fgets(line, sizeof(line), file) != NULL) {
        char key[6];
        char string[STRSIZE];
        sscanf(line, "%5s %[^\n]", key, string); //считываем значения

        value element;
        strcpy(element.key, key); //добавляем их к элементу
        strcpy(element.string, string);
        resizeVector(table, sizeVector(table) + 1);
        writeVector(table, sizeVector(table) - 1, element); 
    }

    fclose(file);

    int size = sizeVector(table);
    printf("Исходная таблица выглядит так:\n");
    printf("|============================================|\n");
    printf("|  Ключ  | Значение                          |\n");
    printf("|============================================|\n");
    for (int i = 0; i < size; i++) {
        value tmp = loadVector(table, i);
        printf("| %6s | %-41s \n", tmp.key, tmp.string);
    }
    printf("|============================================|\n");
    char find[6]; //переменная для поиска по ключу
    int choose = 1;
    while(choose) {
        printMenu();
        scanf("%d", &choose);
        switch(choose) {
            case 0: //выход
                choose = 0;
                destroyVector(table);
                free(table);
                return 0;
                break;
            case 1: //сортировка
                sortShake(table);
                printTable(table);
                break;
            case 2: //поиск
                if (checkSortTableDescending(table)) {
                    vector* reverseTable = malloc(sizeof(vector));
                    createVector(reverseTable, sizeVector(table));
                    vectorReverse(table, reverseTable);
                    printf("Введите ключ: ");
                    scanf("%5s", find);
                    if (strcmp(binarySearch(reverseTable, find).key, "")) {
                        printf("| %6s | %s |\n", binarySearch(reverseTable, find).key, binarySearch(reverseTable, find).string);
                    } else {
                        printf("Указанного ключа в таблице нет\n");
                    }
                    destroyVector(reverseTable);
                    free(reverseTable);
                    break;
                } else if (checkSortTable(table) == 0) { //если таблица не отсортирована
                    printf("Для начала отсортируйте таблицу!\n");
                    break;
                } else {
                    printf("Введите ключ: ");
                    scanf("%5s", find);
                    if (strcmp(binarySearch(table, find).key, "")) {
                        printf("| %6s | %s |\n", binarySearch(table, find).key, binarySearch(table, find).string);
                    } else {
                        printf("Указанного ключа в таблице нет\n");
                    }
                    break;
                }
            case 3: //вывод таблицы
                printTable(table);
                break;
            case 4:
                rewriteFile(argv[1], table);
                printf("Файл успешно перезаписан!\n");
                break;
            default:
                printf("Указанного действия не существует!\n");
                break;
            
        }
    }
    return 0;
}
