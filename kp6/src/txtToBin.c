#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/abiturient.h"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage:\n\t./convert FILE_FROM FILE_TO\n");
        exit(1);
    }

    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "wb");

    if (!in || !out) {
        printf("I/O Error: Can't open file.\n");
        exit(1);
    }

    abiturient student;
    while (fgets(student.surname, STRSIZE, in)) {
        fgets(student.initials, STRSIZE, in);
        fgets(student.sex, STRSIZE, in);
        fscanf(in, "%d", &student.schoolNum);
        fgets(student.medal, STRSIZE, in);
        fgets(student.composition, STRSIZE, in);

        

        int numExams;
        fscanf(in, "%d", &numExams);
        for (int i = 0; i < numExams; i++) {
            node* exam = (node*)malloc(sizeof(node));
            fscanf(in, "%s", exam->data.subject);
            fscanf(in, "%d", &(exam->data.ball));
            exam->next = student.examStats;
            exam->prev = NULL;
            if (student.examStats) {
                student.examStats->prev = exam;
            }
            student.examStats = exam;
        }

        abiturientWriteBin(&student, out);

        // Пропускаем символ новой строки
        fgetc(in);
    }

    fclose(in);
    fclose(out);
    return 0;
}