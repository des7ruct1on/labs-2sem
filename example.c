#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/abiturient.h"

void printMenu() {
    printf("\t0)выход\n");
    printf("\t1)информация об абитуриенте\n");
    printf("\t2)добавление абитуриента\n");
    printf("\t3)найти абитуриента-немедалистов с общим баллов выше среднего\n");
    printf("\t4)удаление абитуриента\n");
    printf("\t5)помощь с выбором команды\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Вы должны запускать программу с базой данных\n");
        exit(1);
    }
    char filename[STRSIZE];
    strncpy(filename, argv[1], STRSIZE - 1);
    filename[STRSIZE - 1] = '\0';
    FILE* file;
    char* ext = strrchr(filename, '.');
    bool isBinary = false;
    if (strcmp(ext, ".txt") == 0 || ext == NULL) {
        printf("Вы используете .txt файл для работы\n");
    } else if (strcmp(ext, ".bin") == 0 || ext != NULL) {
        isBinary = true;
        printf("Вы используете .bin файл для работы\n");
    } else {
        fprintf(stderr, "Некорректное расширение файла!\n");
        exit(2);
    }
    char line[1000];
    HashTable* table = malloc(sizeof(HashTable));
    initHashTable(table);
    if(!isBinary) {
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка, не удалось открыть файл");
            exit(1);
        }
        while(fgets(line, 1000, file) != NULL) {
            abiturient* abit = newAbiturient();
            //printf("%s\n", line);
            csvRead(abit, line);
            char* surname = getSurname(abit);

            insertElement(table, surname, abit);
        }
    } else {
        file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Ошибка, не удалось открыть файл");
            exit(1);
        }
        while (true) {
            abiturient* abit = newAbiturient();
            if (abiturientReadBin(abit, file) == 0) {
                break;
            }

            char* surname = getSurname(abit);

            insertElement(table, surname, abit);
        }
    }

    char choose[STRSIZE];
    printf("Выберите действие\n");
    while(strcmp(choose, "exit") != 0) {
        printAbiturientStr(table);
        int len = strlen(choose);
        fgets(choose, sizeof(choose), stdin);
        if (choose[len - 1] == '\n') {
            choose[len - 1]= '\0';
        }
        char* cmd = strtok(choose, " ");
        if (cmd == NULL) {
            printf("Некорректная команда!\n");
            continue;
        }
        int lenCmd = strlen(cmd);
        char* arg = choose + lenCmd + 1;
        if (strcmp(cmd, "help") == 0) {
            printMenu();
        } else if (strcmp(cmd, "add") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                continue;
            }
            abiturient* abit;
            if (isBinary) {
                abit = addAbiturientBin(filename, arg);
            } else {
                abit = addAbiturient(filename, arg);
            }
            if (abit == NULL) {
                printf("Ошибка при попытке добавления!\n");
                continue;
            }
            insertElement(table, getSurname(abit), abit);
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка: добавьте имя\n");
                continue;
            }
            if (file != NULL) {
                fclose(file);
            }
            if (isBinary) {
                removeStudentBin(filename, arg);
                file = fopen(filename, "rb");
            } else {
                removeStudent(filename, arg);
                file = fopen(filename, "r");
            }
            if (file == NULL) {
                perror("Ошибка при работе с файлом");
                exit(1);
            }
            removeElement(table, arg);
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Ошибка! Добавьте имя абитуриента\n");
                continue;
            }
            abiturient* find = findElement(table, arg);
            if (find == NULL) {
                printf("Не удается найти абитуриента: %s\n", arg);
                continue;
            }
            printAbiturientChars(find);
        } else if (strcmp(cmd, "table") == 0) {
            printAbiturientStr(table);
        } else if (strcmp(cmd, "task") == 0) {
            printf("Неизвестная команда!\n");
        } else {
            printf("Неизвестная команда!\n");
        }


        clearHashTable(table);
        free(table);
        fclose(file);
        return 0;
    }

} 