/*
В файле input.txt записан некоторый текст, общая длина
которого заранее не известна (можно считать,
что длина каждой строки не превосходит 4000 символов).
В первой строке файла записаны ровно два слова (назовем
первое — В, второе — Е). Требуется переписать в файл
output.txt только те слова, начало которых совпадает
sс В, а конец совпадает с Е. Слова надо выводить в том
порядке, в котором они следуют в исходном тексте, и по
одному слову в строке. В случае совпадения слов В и Е
эти слова из первой строки файла input.txt в файл
output.txt не переписываются
*/
#include <stdio.h>
#define LENGTH 4000

int length(char* word) {
    int i;
    for (i = 0; word[i] != '\0'; i++) {}
    return i;
}

int begin_matches(char word[], char B[]) {
    int length_B    = length(B);
    int i;
    for (i = 0; i < length_B; ++i) {
        if (word[i] == B[i])
            continue;
        else
            break;
    }

    if (i == length_B)
        return 1;
    else
        return 0;
}

int end_matches(char word[], char E[]) {
    int length_word = length(word);
    int length_E    = length(E);
    int i;
    for (i = 0; i < length_E; ++i) {
        if (word[length_word - i - 1] == E[length_E - i - 1])
            continue;
        else
    break;
    }
    if (i == length_E)
        return 1;
    else
        return 0;
}

int main() {
    FILE *inp;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("Error reading file!\n");
        return -1;
    }
    char B[LENGTH/2 + 1], E[LENGTH/2 + 1];

    if (fscanf(inp, "%s%s", B, E) != 2) {
        printf("There are no B or E\n");
        return -1;
    }
    char word[LENGTH + 1];
    FILE* out = fopen("output.txt", "w");

    while (fscanf(inp, "%s", word) == 1) {
        if (begin_matches(word, B) && end_matches(word, E))
            fprintf(out, "%s\n", word);
    }
}
