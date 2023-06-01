#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/abiturient.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage:\n\t./generate FILE_BINARY FILE_TEXT\n");
        exit(1);
    }

    FILE* in = fopen(argv[1], "rb");
    FILE* out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("I/O Error: Can't open file.\n");
        exit(1);
    }

    abiturient student;

    while (abiturientReadBin(&student, in)) {
        abiturientWriteTxt(&student, out);

        // Записываем символ новой строки между абитуриентами
        fprintf(out, "\n");
    }

    fclose(in);
    fclose(out);
    return 0;
}
