/*
Реализовать инструкции типа #define и #undef,
то есть выполнить указанные подстановки в
области их задания. Пробельные промежутки
следует оставить без изменения.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Чтобы работать сразу с несколькими дефайнами
// нам нужно будет иметь массив из таких структур
// flag нужен для того, чтобы легко работать с undef
struct Node  {
    int flag;
    char key[256];
    char value[256];
};
typedef struct Node NODE;

// Проверить ялвяется ли символ пустым местом
int is_white_space(char c) {
    return (c == ' ') || (c == '\n') || (c == '\t');
}
// Найти макрос needle в строчке haystack
// amount_of_words - количество аргументов,
// которое принимает макрос
int search_macros(char haystack[], char needle[], int amount_of_words)  {
    // Заводим указатель it на начало
    char *it = haystack;
    int counter = 0, inword = 0;
    // ищем решетку
    do {
        if (!is_white_space(*it)) {
            // если мы нашли что-то кроме решетки
            // возвращаем 0
            if (*it != '#') {
                return 0;
            } else {
                break;
            }
        }
    } while (*it++);
    // проверяем есть ли в haystack наш needle
    it = strstr(haystack, needle);
    if (it != NULL) {
        // если есть, то сдвигаем указатель
        it += strlen(needle);
        // Считаем количество слов после needle
        do {
            if (is_white_space(*it) && inword) {
                inword = 0;
                counter++;
            } else {
                inword = 1;
            }
        } while (*it++);
    }
    // если количество слов совпадает с требуемым, то все ок
    if (counter == amount_of_words)
        return 1;
    return 0;
}
int is_define(char line[]) {
    return search_macros(line, "define ", 2);
}
int is_undef(char line[]) {
    return search_macros(line, "undef ", 1);
}
// Считаем количество define для размера массива
int count_defines(FILE* inp) {
    int count = 0;
    size_t length_buff = 0;
    char * line = NULL;
    int chars_read = 0;
    while ((chars_read = getline(&line, &length_buff, inp)) >= 0) {
        if (is_define(line))
            count++;
    }
    free(line);
    rewind(inp);
    return count;
}

char* try_redefine(NODE* array, int size, char* word) {
    // Проходим дважды, чтобы разобрать случай вложенного
    // макроса
    for (int i = 0; i < size; i++) {
        for (int i = 0; i < size; i++)
            if ((strcmp(word, array[i].key) == 0) && array[i].flag == 1)
                word = array[i].value;
    }
    return word;
}

void print_to_out(FILE* out, FILE* inp, NODE* array) {
    size_t length = 0;
    char current;
    char word[256];
    char temp[256];
    char *line;
    int i = 0, is_newline = 1;

    while ((current = fgetc(inp)) != EOF) {
        if (is_white_space(current)) {
            if (current == '\n')
                is_newline = 1;
            fputc(current, out);
        } else if (is_newline && current == '#') {
            fseek(inp, -1, SEEK_CUR);
            getline(&line, &length, inp);
            if (is_define(line)) {
                sscanf(line, "%s%s%s", word, array[i].key, array[i].value);
                array[i].flag = 1;
                i++;
            } else if (is_undef(line)) {
                sscanf(line, "%s%s", temp, word);
                for (int j = 0; j < i; j++) {
                    if (strcmp(word, array[j].key) == 0) {
                        array[j].flag = 0;
                    }
                }
            }
            fputs(line, out);
            is_newline = 0;
        } else {
            fseek(inp, -1, SEEK_CUR);
            fscanf(inp, "%s", word);
            fprintf(out, "%s", try_redefine(array, i, word));
            is_newline = 0;
        }
    }
    free(line);
    rewind(inp);
}
int main() {
    FILE* inp, *out;
    NODE* define_array;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("Cannot open file!\n");
        return -1;
    }

    define_array = (NODE*)malloc(count_defines(inp)*sizeof(NODE));
    if (define_array == NULL) {
        printf("Cannot malloc!\n");
        fclose(inp);
        return -1;
    }
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("Cannot open file!\n");
        free(define_array);
        fclose(inp);
        return -1;
    }
    print_to_out(out, inp, define_array);
    free(define_array);
    fclose(inp);
    fclose(out);
}
