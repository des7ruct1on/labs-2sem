#include "../headers/abiturient.h"
#include <string.h>

char* getSurname(abiturient* s) {
    if(s == NULL) {
        return "";
    }
    return s->surname;
}

char* getInitials(abiturient* s) {
    if(s == NULL) {
        return "";
    }
    return s->initials;
}

void* getTableChars(abiturient* s, const char* key) {
    hashTable* tmp = s->chars;
    return htableGetFirst(tmp, key)->data;
}


abiturient* newAbiturient() {
    abiturient* s = malloc(sizeof(abiturient));
    if (s == NULL) {
        return NULL;
    }
    strcpy(s->surname, "");         // Use strcpy to initialize character arrays
    strcpy(s->composition, "");
    strcpy(s->initials, "");
    strcpy(s->medal, "");
    strcpy(s->sex, "");
    
    s->examBall = 0;
    s->schoolNum = 0;

    s->chars = initTable(59);
    hashTable* listChars = s->chars;
    htableInsert(listChars, "surname", s->surname);
    htableInsert(listChars, "initials", s->initials);
    htableInsert(listChars, "sex", s->sex);
    htableInsert(listChars, "schoolNum", &(s->schoolNum));
    htableInsert(listChars, "medal", s->medal);
    htableInsert(listChars, "composition", s->composition);
    htableInsert(listChars, "examBall", &(s->examBall));
    htableInsert(listChars, "balls", &(s->balls));
    return s;
}


abiturient* addAbiturient(const char* filename, char* in, hashTable* table) {
    FILE* newFile = fopen(filename, "a+"); //openning with a+ key to add to the end
    if (newFile == NULL) {
        perror("Error");
        exit(1);
    }
    fseek(newFile, 0, SEEK_END);
    fseek(newFile, -1, SEEK_CUR);
    char lastChar = fgetc(newFile);

    if(lastChar == '\n' || ftell(newFile) == 0) {
        rewind(newFile);
        fprintf(newFile, "%s", in);
    } else {
        rewind(newFile);
        fprintf(newFile, "\n%s", in);
    }

    abiturient* s = newAbiturient();
    if (csvRead(s, newFile) != 0) {
        return NULL;
    }
    char* surname = getSurname(s);
    char* initials = getInitials(s);
    fclose(newFile);
    printf("%s %s has added to the table.\n", surname, initials);
    return s;
}

abiturient* addAbiturientBin(const char* filename, char* in, hashTable* table) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Error");
        exit(1);
    }
    abiturient* abit = newAbiturient();
    if (csvRead(abit, in) != 0) {
        return NULL;
    }
    char* surname = getSurname(abit);
    char* initials = getInitials(abit);
    abiturientWriteBin(abit, file);
    fclose(file);
    printf("%s %s has added to the table.\n", surname, initials);
    return abit;
}

int removeStudent(const char* file, const char* id) {
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        return -1;
    }

    char tmpFile[L_tmpnam];
    tmpnam(tmpFile);
    FILE* tmp = fopen(tmpFile, "w");
    if (tmpFile == NULL) {
        printf("Can`t create file\n");
        fclose(fp);
        return -2;
    }

    char line[STRSIZE];
    bool found = false;
    while(fgets(line, sizeof(line), fp) != NULL) {
        if(strncmp(line, id, strlen(id)) != 0) {
            found = true;
            continue;
        }
        fputs(line, tmp);
    }
    fclose(fp);
    fclose(tmp);

    int removef = remove(file);
    int renamef = rename(tmp, file);
    if (removef != 0) {
        printf("Error removing file\n");
        return -3;
    }
    if (renamef != 0) {
        perror("Error renaming file\n");
        return -4;
    }
    if (!found) {
        printf("This abiturient was not found in file: %s", file);
        return -5;
    } else {
        printf("Удаление завершено!");
        return 0;
    }
}

int removeStudentBin(const char* file, const char* id) {
    FILE* fp = fopen(file, "rb");
    if (fp == NULL) {
        return -1;
    }

    char tmpFile[L_tmpnam];
    tmpnam(tmpFile);
    FILE* tmp = fopen(tmpFile, "wb");
    if (tmpFile == NULL) {
        printf("Can`t create file\n");
        fclose(fp);
        return -2;
    }

    bool found = false;
    abiturient* abit = newAbiturient();
    while(abiturientReadBin(abit, file) != 0) {
        char* surname = abit->surname;

        if(strncmp(surname, id, strlen(surname)) == 0) {
            found = true;
            continue;
        }
        abiturientWriteBin(abit, tmp);
    }
    abiturientFree(abit);
    fclose(fp);
    fclose(tmp);

    int removef = remove(file);
    int renamef = rename(tmp, file);
    if (removef != 0) {
        printf("Error removing file\n");
        return -3;
    }
    if (renamef != 0) {
        perror("Error renaming file\n");
        return -4;
    }
    if (!found) {
        printf("This abiturient was not found in file: %s", file);
        return -5;
    } else {
        printf("Удаление завершено!");
        return 0;
    }
}


void printAbiturientChars(abiturient* s) {
    if (s == NULL) {
        return;
    }
    hashTable* ht = s->chars;
    if (htableGetFirst(ht, "name") == NULL) {
        return;
    }
    char* surname = (char*)htableGetFirst(ht, "surname")->data; 
    char* initials = (char*)htableGetFirst(ht, "initials")->data; 
    char* sex = (char*)htableGetFirst(ht, "sex")->data; 
    int* schoolNum = (int*)htableGetFirst(ht, "schoolNum")->data;
    char* medal = (char*)htableGetFirst(ht, "medal")->data; 
    char* composition = (char*)htableGetFirst(ht, "composition")->data; 
    
    printf("|============================================|\n");
    printf("|\tAbiturient: %s %s                         |\n", surname, initials);
    printf("|\tSex: %s                                   |\n", sex);
    printf("|\tSchool number: %d                         |\n", schoolNum);
    printf("|\tHas gold medal: %s                        |\n", medal);
    printf("|\tPassed composition: %s                    |\n", composition);
    int numSubjects = 0;
    for (int i = 0; i < 20; i++) {
        if (strlen(s->balls.ob[i]) > 0) {
            numSubjects++;
        }
    }
    for (int i = 0; i < numSubjects; i++) {
        char* subject = s->balls.ob[i];
        Item mark = s->balls.ball[i];
        printf("|\t%-24s%-16d|\n", subject, mark);
    }
    printf("|============================================|\n");
    return;
}

void abiturientFree(abiturient* s) {
    if (s == NULL) {
        return;
    }
    free(s->surname);
    free(s->initials);
    free(s->sex);
    free(s->schoolNum);
    free(s->medal);
    free(s->composition);
    free(s->examBall);
    freeHashTable(s->chars);
    for (int i = 0; i < 20; i++) {
        char* subject = s->balls.ob[i];
        Item mark = s->balls.ball[i];
        free(subject);
        free(mark);
    }
    free(s);
}

int readFromFile(const char* type, void* abiturPtr, char* in) {
    int res = 0;
    switch(type[1]) {
        case 's': {
            int len = strlen(in);
            if (len > 0 && in[len - 1] == '\n') {
                in[len - 1] = '\0';
            }
            strcpy(*(char**)abiturPtr, in);
            break;
        }
        case 'd': {
            char* lastPtr;
            int data = strtol(in, &lastPtr, 10);
            if (in == lastPtr || data <= 0) {
                res = -1;
            } else {
                *(int*)abiturPtr = data;
            }
            break;
        }
        default: {
            perror("Error: incorrect type");
            break;
        }

    }
    return res;
}

int csvRead(abiturient* abit, char* in) {
    char* token = strtok(in, " ");

    // Surname
    if (token == NULL) {
        fprintf(stderr, "Error: missing surname\n");
        return -1;
    }
    strcpy(abit->surname, token);

    // Initials
    token = strtok(NULL, " ");
    if (token == NULL) {
        fprintf(stderr, "Error: missing initials\n");
        return -1;
    }
    strcpy(abit->initials, token);

    // Sex
    token = strtok(NULL, " ");
    if (token == NULL) {
        fprintf(stderr, "Error: missing sex\n");
        return -1;
    }
    strcpy(abit->sex, token);

    // School number
    token = strtok(NULL, " ");
    if (token == NULL) {
        fprintf(stderr, "Error: missing school number\n");
        return -1;
    }
    abit->schoolNum = atoi(token);

    // Medal
    token = strtok(NULL, " ");
    if (token == NULL) {
        fprintf(stderr, "Error: missing medal\n");
        return -1;
    }
    strcpy(abit->medal, token);

    // Composition
    token = strtok(NULL, " ");
    if (token == NULL) {
        fprintf(stderr, "Error: missing composition\n");
        return -1;
    }
    strcpy(abit->composition, token);

    // Subject Balls
    for (int i = 0; i < 20; i++) {
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error: missing subject ball\n");
            return -1;
        }
        strcpy(abit->balls.ob[i], token);

        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error: missing subject mark\n");
            return -1;
        }
        abit->balls.balls[i] = atoi(token);
    }

    return 0;
}


void addReadAbitur(char* surname, char list[TABLESIZE][STRSIZE], int* count, hashTable* table) {
    bool isRead = false;
    if (htableGetFirst(table, surname) != NULL) {
        for (int i = 0; i < *count; i++) {
            if (strcmp(list[i], surname) == 0) {
                isRead = true;
                break;
            }
        }
        if (!isRead) {
            strncpy(list[*count], surname, 50); ////////
            *count = *count + 1;
        }
    }
    return;
}

void specstostr(abiturient* ab, char* str, size_t len)
{
    if (ab == NULL || str == NULL || len <= 0)
        return;

    snprintf(str, len, "Surname: %s; Initials: %s; Sex: %s; School Number: %d; Medal: %s; Composition: %s; Exam Ball: %d",
             ab->surname, ab->initials, ab->sex, ab->schoolNum, ab->medal, ab->composition, ab->examBall);

    // Append subjectBall information
    size_t i;
    for (i = 0; i < 20; i++)
    {
        snprintf(str + strlen(str), len - strlen(str), "; Subject %zu: %s - %d", i, ab->balls.ob[i], ab->balls.ball[i]);
    }
    return;
}


int abiturientReadTxt(abiturient *s, FILE *in) {
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, "%s", s->sex);
    fscanf(in, "%d", s->schoolNum);
    fscanf(in, "%s", s->medal);
    fscanf(in, "%s", s->composition);
    for (int i = 0; i < s->examBall; i++) {
        fscanf(in, "%s", (s->balls.ob[i]));
        fscanf(in, "%d", &(s->balls.ball[i]));
    }
    return !feof(in);
}

void abiturientWriteTxt(abiturient *s, FILE *file) {
    fprintf(file, "%s", s->surname);
    fprintf(file, "%s", s->initials);
    fprintf(file, "%s", s->sex);
    fprintf(file, "%d", s->schoolNum);
    fprintf(file, "%s", s->medal);
    fprintf(file, "%s", s->composition);
    for (int i = 0; i < s->examBall; i++) {
        fprintf(file, "%s", (s->balls.ob[i]));
        fprintf(file, "%d", &(s->balls.ball[i]));
    }
    fprintf(file, "\n");
}

int abiturientReadBin(abiturient *s, FILE *in) {
    fread(s->surname, sizeof(char), STRSIZE, in);
    fread(s->initials, sizeof(char), STRSIZE, in);
    fread(s->sex, sizeof(char), STRSIZE, in);
    fread(s->schoolNum, sizeof(char), STRSIZE, in);
    fread(s->medal, sizeof(char), STRSIZE, in);
    fread(s->composition, sizeof(char), STRSIZE, in);
    for (int i = 0; i < s->examBall; i++) {
        fread((s->balls.ob[i]), sizeof(char), STRSIZE, in);
        fread(&(s->balls.ball[i]), sizeof(int), 1, in);
    }
    return !feof(in);
}

void abiturientWriteBin(abiturient *s, FILE *out) {
    fwrite(s->surname, sizeof(char), STRSIZE, out);
    fwrite(s->initials, sizeof(char), STRSIZE, out);
    fwrite(s->sex, sizeof(char), STRSIZE, out);
    fwrite(s->schoolNum, sizeof(char), STRSIZE, out);
    fwrite(s->medal, sizeof(char), STRSIZE, out);
    fwrite(s->composition, sizeof(char), STRSIZE, out);
    for (int i = 0; i < s->examBall; i++) {
        fwrite((s->balls.ob[i]), sizeof(char), STRSIZE, out);
        fwrite(&(s->balls.ball[i]), sizeof(int), 1, out);
    }
}