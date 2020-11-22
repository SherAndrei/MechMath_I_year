// В файле input.txt записан некоторый текст,
// общая длина которого заранее не известна
// (можно считать, что длина каждой строки
// не превосходит 4000 символов). Требуется
// заключить каждое слово текста в квадратные
// скобки, например вот так [слово] [еще] [и] [т.д.].
// Словом называется группа подряд идущих
// непробельных символов (пробельный символ
// - {’ ’, ’\n’, ’ \t’}).
// Преобразованный текст нужно вывести в файл output.txt

#include <stdio.h>

#define LENGTH 4000

int is_white_space(char letter) {
    return (letter == ' ') || (letter == '\n') || (letter == '\t');
}

int main() {
    FILE* inp;

    inp = fopen("input.txt", "r");

    if (!inp) {
        printf("Error: reading file!");
        fclose(inp);
        return -1;
    } else {
        FILE* out;
        out = fopen("output.txt", "w");

        char current, last = ' ';
        // Считываем с инпута текущий (current) char, если он конец файла то ничего не делаем
        while ((current = fgetc(inp)) != EOF) {
            // если текущий не пробел, а прошлый пробел, то ставим скобочку
            if (!is_white_space(current) && is_white_space(last))
                fputc('[', out);
            // если текущий пробел, а прошлый не пробел, то ставим другую скобочку
            else if (is_white_space(current) && !is_white_space(last))
                fputc(']', out);

            // в остальных случаях печатаем текущий
            fputc(current, out);
            // теперь последний это текущий
            last = current;
        }
        // на случай если текущий это конец файла, а прошлый не пробел
        if (!is_white_space(last))
            fputc(']', out);

        fclose(out);
    }
    fclose(inp);
    return 0;
}
