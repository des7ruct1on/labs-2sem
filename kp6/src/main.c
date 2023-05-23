#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/abiturient.h"
#include "../headers/table.h"

void printMenu() {
    printf("\tinfo - information about abiturient\n");
    printf("\tadd - addition of abiturient\n");
    printf("\ttask - find out non-medal abiturients with total ball > average\n");
    printf("\tremove - deletion of abiturient\n");
    printf("\thelp - checking commands which are available to choose\n");
    printf("\texit - stop the programm\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("You should run main.out with database file\n");
        exit(1);
    }
    char filename[STRSIZE];
    strncpy(filename, argv[1], STRSIZE - 1);
    filename[STRSIZE - 1] = '\0';
    FILE* file;
    char* ext = strrchr(filename, '.');
    bool isBinary = false;
    if (strcmp(ext, ".txt") == 0 || ext == NULL) {
        printf("You are using .txt file\n");
    } else if (strcmp(ext, ".bin") == 0 || ext != NULL) {
        isBinary = true;
        printf("You are using .bin file\n");
    } else {
        fprintf(stderr, "Invalid file, check extension please.\n");
        exit(2);
    }

    char line[STRSIZE];
    hashTable* table = initTable(TABLESIZE);
    char readStudents[TABLESIZE][STRSIZE];
    int count = 0;
    if(!isBinary) {
        file = fopen(filename, "r");
        if (file != NULL) {
            perror("Error");
            exit(1);
        }
        while(fgets(line, STRSIZE, file) != NULL) {
            abiturient* abit = newAbiturient();
            csvRead(abit, line);
            char* surname = getSurname(abit);

            htableInsert(table, surname, abit);
        }
    } else {
        file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Error");
            exit(1);
        }
        while (true) {
            abiturient* abit = newAbiturient();
            if (abiturientReadBin(abit, file) == 0) {
                break;
            }

            char* surname = getSurname(abit);

            htableInsert(table, surname, abit);
        }
    }

    char choose[STRSIZE];
    printf("Enter a request\n");
    while(strcmp(choose, "exit") != 0) {
        int len = strlen(choose);
        fgets(choose, sizeof(choose), stdin);
        if (choose[len - 1] == '\n') {
            choose[len - 1]= '\0';
        }
        char* cmd = strtok(choose, " ");
        if (cmd == NULL) {
            printf("Invalid command!\n");
            continue;
        }
        int lenCmd = strlen(cmd);
        char* arg = choose + lenCmd + 1;
        if (strcmp(cmd, "info") == 0) {
            printMenu();
        } else if (strcmp(cmd, "add") == 0) {
            if (arg[0] == '\0') {
                printf("Error: add name\n");
                continue;
            }
            abiturient* abit;
            if (isBinary) {
                abit = addAbiturientBin(filename, arg, table);
            } else {
                abit = addAbiturient(filename, arg, table);
            }
            if (abit == NULL) {
                printf("Error while trying to add abiturient!\n");
                continue;
            }
            htableInsert(table, getSurname(abit), abit);
            addReadAbitur(getSurname(abit), readStudents, &count, table);
        } else if (strcmp(cmd, "remove") == 0) {
            if (arg[0] == '\0') {
                printf("Error: add name of\n");
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
                perror("Error");
                exit(1);
            }
            hashNode* tmp = htableGetFirst(table, arg);
            while(tmp != NULL) {
                abiturientFree(tmp->data);
                tmp->data = NULL;
                hashNode* nxt = tmp->next;
                free(tmp);
                table->table[hash(table, arg)] = NULL;
                tmp = nxt;
            }
 
        } else if (strcmp(cmd, "info") == 0) {
            if (arg[0] == '\0') {
                printf("Error: add name of\n");
                continue;
            }
            hashNode* tmp = htableGetFirst(table, arg);
            if (tmp == NULL) {
                printf("Can`t find student %s\n", arg);
                continue;
            }
            for (int i = 1; tmp != NULL; i++) {
                abiturient* tmpNode = tmp->data;
                printf("|Number: %d\n", i);
                printf("%d",tmpNode->schoolNum);
                //
                tmp = htGetNext(tmpNode);

            }
        } else if (strcmp(cmd, "table") == 0) {
            if (printTable(table) == 0) {
                printf("Table is empty\n");
            }
        } else if (strcmp(cmd, "task") == 0) {

        } else if (strcmp(cmd, "q") == 0) {
            continue;
        } else {
            printf("Unknown command!\n");
        }

        for (int i = 0; i < table->size; i++) {
            if (table->table[i] == NULL) {
                continue;
            }
            hashNode* tmp = table->table[i];
            while (tmp != NULL) {
                abiturientFree(tmp->data);
                tmp->data = NULL;
                hashNode* nxt = tmp->next;
                free(tmp);
                table->table[i] = NULL;
                tmp = nxt;
            }
        }
        hashTableFree(table);
        fclose(file);
        return 0;
    }

} 