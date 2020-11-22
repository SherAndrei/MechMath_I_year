/*
В файле input.txt записан некоторый текст, общая длина
которого заранее не известна (можно считать, что длина каждой
строки не превосходит 4000 символов). В первой строке файла
записано одно единственное слово (назовем его W). Требуется
вывести в файл output.txt все "слова" исходного файла, у которых
первый символ совпадает хотя бы с одним символом из слова W.
Эти слова нужно вывести в том порядке, в котором они следуют
в исходном файле, каждое слово в отдельной строке, само слово
W выводить не надо.
*/
#include <stdio.h>

#define LENGTH 4000

char * Strchr(const char *s, int c) {
    while (*s != (char)c)
        if (!*s++)
            return 0;
    return (char *)s;
}

int main() {
    FILE *inp;
    char target[LENGTH];
    inp = fopen("input.txt", "r");
    if (!inp) {
        printf("Error reading file!");
        fclose(inp);
        return -1;
    } else if (!fgets(target, LENGTH, inp)) {
        printf("File is empty!");
        fclose(inp);
        return -2;
    } else {
        char word[LENGTH];
        FILE* out;
        out = fopen("output.txt", "w");

        while (fscanf(inp, "%s", word) != EOF) {
            if (Strchr(target, word[0]))
                fprintf(out, "%s\n", word);
        }
        fclose(out);
    }
    fclose(inp);
}