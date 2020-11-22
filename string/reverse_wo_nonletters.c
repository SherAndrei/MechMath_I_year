/*
Дана строка S. Требуется преобразовать её так, чтобы все символы,
являющиеся символами латинского алфавита, оказались записаны
в обратном порядке, а все остальные символы сохранили свои позиции.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isletter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int get_length(FILE* inp) {
    char c;
    int count = 0;
    for (c = fgetc(inp); c != EOF && c != '\n'; c = fgetc(inp))
        count++;

    rewind(inp);
    return count;
}

void reverse_without_nonletters(char* str, int length) {
    int i, j = 0;
    // Массив только для букв
    char letters[length];
    // Заполняем буквенный массив
    for (i = 0; i < length; i++) {
        if (isletter(str[i])) {
            letters[j] = str[i];
            j++;
        }
    }
    // Вставляем буквы в обратном  порядке
    for (i = 0; i < length; i++) {
        if (isletter(str[i])) {
            str[i] = letters[j - 1];
            j--;
        }
    }
}

int main() {
    FILE* inp;
    int length;
    char* str = NULL;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("Cannot open file!\n");
        return -1;
    }

    length = get_length(inp);
    printf("%d\n", length);
    str = (char*)malloc(length + 1);
    fgets(str, length + 1, inp);

    printf("Before: %s\n", str);
    reverse_without_nonletters(str, length);
    printf("After:  %s\n", str);
    free(str);
    fclose(inp);
}
