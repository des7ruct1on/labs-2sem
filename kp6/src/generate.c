#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/abiturient.h"
#include "io.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage:\n\t./generate FILE_FROM FILE_TO\n");
        exit(0);
    }

    FILE *in  = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        printf("I/O Error: can't open file.\n");
        exit(1);
    }

    abiturient s;

    while (abiturientReadTxt(&s, in)) {
        abiturientWriteBin(&s, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}