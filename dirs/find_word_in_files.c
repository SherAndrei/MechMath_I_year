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

/*
Проверяем есть ли в файле file искомое слово word
*/
int is_contains(FILE* file, const char* word) {
    size_t length = 0;
    char* line = NULL;
    int char_count = 0;
    // идем по всем строчкам в файле и ищем слово
    while ((char_count = getline(&line, &length, file)) > 0)
        if (strstr(line, word) != NULL)
            return 1;

    free(line);
    rewind(file);
    return 0;
}

/*
Присоединяем к пути название папки, если надо, то
добавляем разделитель
char path[] = "";
если вызываем attach(path, "home", 0) --> path == "home"
если вызываем attach(path, "home", '/') --> path == "home/"
*/
void attach(char* path, const char* foldername, char delim) {
    strncat(path, foldername, PATH_MAX);
    if (delim != 0)
        strncat(path, &delim, 1);
}

/*
Кушаем с конца пути последние length символов
*/
void detach(char* path, size_t length) {
    path[strlen(path) - length] = '\0';
}

/*
Проходим по всем файлам в папке foldername, пытаемся
открыть файлы, если получается, то ищем в них слово
Если нашли искомое слово, то печатаем имя файла с путем
*/
void lookup(char* path, const char* foldername, const char* word) {
    struct dirent* dp;
    DIR* dir;
    FILE* file;

    // Присоединяем к пути текущую папку с разделитем
    // для винды используется разделитель \
    // для линукса используется разделитель /
    attach(path, foldername, '/');
    // пытаемся открыть папку
    if ((dir = opendir(path)) == NULL) {
        printf("Cannot open folder: %s\n", path);
        detach(path, strlen(foldername) + 1);
        return;
    }
    // проходим по всему содержимому в папке
    while ((dp = readdir(dir)) != NULL) {
        // в каждой папке есть два элемента
        // текущая папка
        if (!strcmp(dp->d_name, "."))
            continue;
        // папка-родитель
        if (!strcmp(dp->d_name, ".."))
            continue;
        // если не написать строчку 81, то мы зациклимся
        // если не написать строчку 84, то мы уйдем в самый корень системы

        // если текущий элемент является папкой
        // вызываем эту функцию заново для подпапки
        if (dp->d_type == DT_DIR) {
            lookup(path, dp->d_name, word);
        } else if (dp->d_type == DT_REG) {
            // иначе присоединяем к пути имя текущего файла
            // пытаемся его открыть
            attach(path, dp->d_name, 0);
            if ((file = fopen(path, "r")) == NULL) {
                printf("Cannot open file: %s\n", path);
                continue;
            }
            // если находим слово, то печатаем
            if (is_contains(file, word))
                printf("%s\n", path);

            // отсоединяем имя файла от пути, чтобы работать дальше
            // и закрываем его
            detach(path, strlen(dp->d_name));
            fclose(file);
        }
    }
    detach(path, strlen(foldername) + 1);
    closedir(dir);
}


// Получаем в качестве аргументов имя папки и слово,
// которое будем искать в файлах
int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("wrong input\n");
        return -1;
    }
    // создаем массив размерa
    // максимального доступного пути до папки и заполянем 0
    char path[PATH_MAX] = {'\0'};
    lookup(path, argv[1], argv[2]);
    return 0;
}
