#include "../headers/abiturient.h"
#include <string.h>

void initHashTable(HashTable* table) {
    for (int i = 0; i < TABLESIZE; i++) {
        table->entries[i].key[0] = '\0';
        table->entries[i].value = NULL;
    }
}

unsigned int hash(const char* key) {
    unsigned int hash = 0;
    unsigned int p = 31;
    unsigned int len = strlen(key);

    for (unsigned int i = 0; i < len; i++) {
        hash = (hash * p) + key[i];
    }

    return hash % TABLESIZE;
}

void insertElement(HashTable* table, const char* key, abiturient* value) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        index = (index + 1) % TABLESIZE;
    }

    strcpy(table->entries[index].key, key);
    table->entries[index].value = value;
}

abiturient* findElement(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            return table->entries[index].value;
        }

        index = (index + 1) % TABLESIZE;
    }

    return NULL;
}

void removeElement(HashTable* table, const char* key) {
    unsigned int index = hash(key);

    while (table->entries[index].value != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            table->entries[index].key[0] = '\0';
            table->entries[index].value = NULL;
            return;
        }

        index = (index + 1) % TABLESIZE;
    }
}

void clearHashTable(HashTable* table) {
    for (int i = 0; i < TABLESIZE; i++) {
        table->entries[i].key[0] = '\0';
        table->entries[i].value = NULL;
    }
}


void pushFront(node** head, value data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;
    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void pushBack(node** head, value data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

void deleteBack(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    if (head->next == NULL) {
        free(head);
        head = NULL;
        return;
    }

    node* current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->prev->next = NULL;
    free(current);
}

void deleteFront(node* head) {
    if (head == NULL) {
        printf("Список пуст!\n");
        return;
    }

    node* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    free(temp);
}

void printList(node* head) {
    node* current = head;
    while (current != NULL) {
        printf("%s %d ", current->data.subject, current->data.ball);
        current = current->next;
    }
    printf("\n");
}

void destroy(node* head) {
    node* current = head;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

int sizeList(node* head) {
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

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

abiturient* newAbiturient() {
    abiturient* s = malloc(sizeof(abiturient));
    if (s == NULL) {
        return NULL;
    }
    strcpy(s->surname, "");         
    strcpy(s->composition, "");
    strcpy(s->initials, "");
    strcpy(s->medal, "");
    strcpy(s->sex, "");

    s->examStats = NULL;

    return s;
}


void readFromLine(abiturient* s, char* line) {
    char* token = strtok(line, " ");
    
    // Считываем первые 6 слов
    strncpy(s->surname, token, STRSIZE - 1);
    s->surname[STRSIZE - 1] = '\0';
    token = strtok(NULL, " ");
    
    strncpy(s->initials, token, STRSIZE - 1);
    s->initials[STRSIZE - 1] = '\0';
    token = strtok(NULL, " ");
    
    strncpy(s->sex, token, STRSIZE - 1);
    s->sex[STRSIZE - 1] = '\0';
    token = strtok(NULL, " ");
    
    s->schoolNum = atoi(token);
    token = strtok(NULL, " ");
    
    strncpy(s->medal, token, STRSIZE - 1);
    s->medal[STRSIZE - 1] = '\0';
    token = strtok(NULL, " ");
    
    strncpy(s->composition, token, STRSIZE - 1);
    s->composition[STRSIZE - 1] = '\0';
    token = strtok(NULL, " ");
    
    s->examStats = NULL;  // Инициализируем список результатов экзаменов
    
    node* current = s->examStats;  // Указатель на текущий элемент списка
    
    // Считываем пары слов (экзамен и балл) и добавляем их в список
    while (token != NULL) {
        value examResult;
        strncpy(examResult.subject, token, STRSIZE - 1);
        examResult.subject[STRSIZE - 1] = '\0';
        token = strtok(NULL, " ");
        
        int ball = atoi(token);
        token = strtok(NULL, " ");
        
        if (current == NULL) {
            pushBack(&(s->examStats), examResult);
            s->examStats->data.ball = ball;
            current = s->examStats;
        } else {
            pushBack(&(current->next), examResult);
            current->next->data.ball = ball;
            current = current->next;
        }
    }
}

void addAbiturient(const char* filename, char* in, HashTable* table) {
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
    readFromLine(s, in);
    char* surname = getSurname(s);
    char* initials = getInitials(s);
    char key[STRSIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    printf("%s", key);
    fclose(newFile);
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insertElement(table, key, s);
}

void addAbiturientBin(const char* filename, char* in, HashTable* table) {
    FILE* file = fopen(filename, "ab");
    if (file == NULL) {
        perror("Ошибка открытия файлы");
        exit(1);
    }
    abiturient* abit = newAbiturient();
    abiturientReadBin(abit, file);
    char* surname = getSurname(abit);
    char* initials = getInitials(abit);
    char key[STRSIZE];
    strcpy(key, surname); // Копируем фамилию в ключ
    strcat(key, " "); // добавляем разделитель
    strcat(key, initials); // Добавляем инициалы в конец ключа
    abiturientWriteBin(abit, file);
    fclose(file);
    printf("%s %s был добавлен в таблицу.\n", surname, initials);
    insertElement(table, key, abit);
}

void removeStudent(const char* file, const char* id, HashTable* table) {
    FILE* tmpFile = tmpfile();
    if (tmpFile == NULL) {
        printf("Не удалось создать временный файл!\n");
        exit(1);
    }

    removeElement(table, id);
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            abiturientWriteTxt(tmp, tmpFile);
        }
    }

    fseek(tmpFile, 0, SEEK_SET);

    FILE* originalFile = fopen(file, "w");
    if (originalFile == NULL) {
        printf("Не удалось открыть файл для записи!\n");
        exit(1);
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), tmpFile)) > 0) {
        fwrite(buffer, 1, bytesRead, originalFile);
    }

    fclose(originalFile);
}



void removeStudentBin(const char* file, const char* id, HashTable* table) {
    FILE* tmpFile = tmpfile();
    if (tmpFile == NULL) {
        printf("Не удалось создать временный файл!\n");
        exit(1);
    }

    removeElement(table, id);
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            abiturientWriteBin(tmp, tmpFile);
        }
    }

    fseek(tmpFile, 0, SEEK_SET);

    FILE* originalFile = fopen(file, "wb");
    if (originalFile == NULL) {
        printf("Не удалось открыть файл для записи!\n");
        exit(1);
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), tmpFile)) > 0) {
        fwrite(buffer, 1, bytesRead, originalFile);
    }
    fclose(originalFile);
    fclose(tmpFile);
}


void printAbiturientChars(abiturient* s) {
    if (s == NULL) {
        return;
    }
    char* surname = getSurname(s);
    char* initials = getInitials(s);
    char* sex = s->sex;
    Item school = s->schoolNum;
    char* medal = s->medal;
    char* comp = s->composition;
    
    printf("|============================================|\n");
    printf("|\tАбитуриент: %s %s                         \n", surname, initials);
    printf("|\tПол: %s                                   \n", sex);
    printf("|\tНомер школы: %d                         \n", school);
    printf("|\tНаличие медали: %s                        \n", medal);
    printf("|\tЗачет по сочинению: %s                    \n", comp);
    
    int numSubjects = sizeList(s->examStats);
    node* tmp = s->examStats;
    int totalBalls = 0;
    for(int i = 0; i < numSubjects; i++) {
        int ball = tmp->data.ball;
        printf("|\tБал по %s: %d                           \n", tmp->data.subject, ball);
        tmp = tmp->next;
        totalBalls += ball;
    }
    printf("|\tСуммарный балл: %d \n", totalBalls);
    printf("|============================================|\n");
}


void abiturientFree(abiturient* s) {
    if (s == NULL) {
        return;
    }
    free(s->surname);
    free(s->initials);
    free(s->sex);
    s->schoolNum = 0;
    free(s->medal);
    free(s->composition);
    destroy(s->examStats);
}

void printAbiturientStr(HashTable* table) {
    printf("| Фамилия | Инициалы | Пол | Номер школы | Наличие медали | Зачет по сочинению |\n");
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            int numSubjects = sizeList(tmp->examStats);
            printf("| %s | %s | %s | %d | %s | %s |\n", tmp->surname, tmp->initials, tmp->sex, tmp->schoolNum, tmp->medal, tmp->composition);
            node* exam = tmp->examStats;
            for (int j = 0; j < numSubjects; j++) {
                printf("| Экзамен %d: %s, балл - %d \n", (j+1), exam->data.subject, exam->data.ball);
                exam = exam->next;
            }
            printf("-----------------\n");
        }
    }
}



int abiturientReadTxt(abiturient* s, FILE* in) {
    fscanf(in, "%s", s->surname);
    fscanf(in, "%s", s->initials);
    fscanf(in, "%s", s->sex);
    fscanf(in, "%d", &(s->schoolNum));
    fscanf(in, "%s", s->medal);
    fscanf(in, "%s", s->composition);

    // Очищаем существующий список экзаменов
    s->examStats = NULL;

    int numExams = 0;
    char subject[STRSIZE];
    int ball;
    while (fscanf(in, "%s %d", subject, &ball) == 2) {
        value exam;
        strcpy(exam.subject, subject);
        exam.ball = ball;

        // Добавляем новый узел в начало списка
        pushFront(&(s->examStats), exam);

        numExams++;
    }

    return numExams > 0;
}



void abiturientWriteTxt(abiturient* s, FILE* file) {
    fprintf(file, "%s ", s->surname);
    fprintf(file, "%s ", s->initials);
    fprintf(file, "%s ", s->sex);
    fprintf(file, "%d ", s->schoolNum);
    fprintf(file, "%s ", s->medal);
    fprintf(file, "%s ", s->composition);
    
    node* current = s->examStats;
    while (current != NULL) {
        value exam = current->data;
        fprintf(file, "%s %d ", exam.subject, exam.ball);
        current = current->next;
    }
    
    fprintf(file, "\n");
}

int abiturientReadBin(abiturient* s, FILE* in) {
    fread(s->surname, sizeof(char), strlen(s->surname) + 1, in);
    fread(s->initials, sizeof(char), strlen(s->initials) + 1, in);
    fread(s->sex, sizeof(char), strlen(s->sex) + 1, in);
    fread(&(s->schoolNum), sizeof(Item), 1, in);
    fread(s->medal, sizeof(char), strlen(s->medal) + 1, in);
    fread(s->composition, sizeof(char), strlen(s->composition) + 1, in);

    // Очищаем существующий список экзаменов
    destroy(s->examStats);
    s->examStats = NULL;

    int numExams = 0;
    char subject[STRSIZE];
    int ball;
    while (fread(subject, sizeof(char), STRSIZE, in) == STRSIZE && fread(&ball, sizeof(int), 1, in) == 1) {
        value exam;
        strcpy(exam.subject, subject);
        exam.ball = ball;

        // Добавляем новый узел в начало списка
        pushFront(&(s->examStats), exam);

        numExams++;
    }

    return numExams > 0;
}


void abiturientWriteBin(abiturient* s, FILE* out) {
    fwrite(s->surname, sizeof(char), STRSIZE, out);
    fwrite(s->initials, sizeof(char), STRSIZE, out);
    fwrite(s->sex, sizeof(char), STRSIZE, out);
    fwrite(&(s->schoolNum), sizeof(Item), 1, out);
    fwrite(s->medal, sizeof(char), STRSIZE, out);
    fwrite(s->composition, sizeof(char), STRSIZE, out);

    node* current = s->examStats;
    while (current != NULL) {
        value exam = current->data;
        fwrite(exam.subject, sizeof(char), STRSIZE, out);
        fwrite(&(exam.ball), sizeof(int), 1, out);
        current = current->next;
    }
}

void task(HashTable* table) {
    float totalBalls = 0;
    int countAbits = 0;
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            countAbits++;
            int numSubjects = sizeList(tmp->examStats);
            node* exam = tmp->examStats;
            for (int j = 0; j < numSubjects; j++) {
                int ball = exam->data.ball;
                totalBalls += ball;
                exam = exam->next;
            }
        }
    }
    float avgBall = totalBalls / countAbits;
    printf("Средний балл среди всех абитуриентов: %f\n", avgBall);
    for(int i = 0; i < TABLESIZE; i++) {
        if (table->entries[i].value != NULL) {
            abiturient* tmp = table->entries[i].value;
            if (tmp == NULL) {
                continue;
            }
            if (strcmp(tmp->medal, "No") == 0) {
                int numSubjects = sizeList(tmp->examStats);
                node* exam = tmp->examStats;
                float balls = 0;
                for (int j = 0; j < numSubjects; j++) {
                    float ball = exam->data.ball;
                    balls += ball;
                    exam = exam->next;
                }
                if (balls > avgBall) {
                    printAbiturientChars(tmp);
                } 
            }
        }
    }
}