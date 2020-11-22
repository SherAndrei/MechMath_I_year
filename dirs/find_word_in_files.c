/*
В этих задачах требуется освоить ввод данных в программу
с помощью командной строки и познакомиться с операциями
получения информации о файлах и каталогах. Для обхода
каталогов наиболее удобно использовать функции opendir,
readdir, и т. д., кроме того можно использовать функцию ftw (см. man 3 opendir или
man 3 ftw ).
Реализовать программу обработки множества файлов, заданных шаблоном
или относящихся к указанному
каталогу. Входные параметры должны задаваться в командной строке.

Для заданного каталога и его подкаталогов определить все файлы, содержащие заданное слово.
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int is_contains(FILE* file, const char* word) {
    size_t length = 0;
    char* line = NULL;
    int char_count = 0;

    while ((char_count = getline(&line, &length, file)) > 0)
        if (strstr(line, word) != NULL)
            return 1;

    free(line);
    rewind(file);
    return 0;
}

void attach(char* path, const char* foldername, char delim) {
    strncat(path, foldername, PATH_MAX);
    if (delim != 0)
        strncat(path, &delim, 1);
}
void detach(char* path, size_t length) {
    path[strlen(path) - length] = '\0';
}


void lookup(char* path, const char* foldername, const char* word) {
    struct dirent* dp;
    DIR* dir;
    FILE* file;

    attach(path, foldername, '\\');
    if ((dir = opendir(path)) == NULL) {
        printf("Cannot open folder: %s\n", path);
        detach(path, strlen(foldername) + 1);
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (!strcmp(dp->d_name, "."))
            continue;
        if (!strcmp(dp->d_name, ".."))
            continue;
        if (dp->d_type == DT_DIR) {
            lookup(path, dp->d_name, word);
        } else if (dp->d_type == DT_REG) {
            attach(path, dp->d_name, 0);
            if ((file = fopen(path, "r")) == NULL) {
                printf("Cannot open file: %s\n", path);
                continue;
            }
            if (is_contains(file, word))
                printf("%s\n", path);

            detach(path, strlen(dp->d_name));
            fclose(file);
        }
    }
    detach(path, strlen(foldername) + 1);
    closedir(dir);
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("wrong input\n");
        return -1;
    }
    char path[PATH_MAX] = {'\0'};
    lookup(path, argv[1], argv[2]);
    return 0;
}
