/*
Дан массив целых чисел A длины N.
К каждому элементу массива A один раз прибавляется
либо число K либо число −K. Таким образом,
получается массив B. Выведите наименьшую
возможную разницу между наибольшим элементом
 массива B и наименьшим элементом массива B.
*/
#include <stdio.h>
#include <stdlib.h>

int Process(int* array, int N, int K) {
    int min, max, in_min, in_max, i;
    in_min = in_max = array[0];
    // Найдем сначала in_min и in_max
    // начальные макс и мин массива А
    for (i = 0; i < N; i++) {
        if (in_min > array[i])
            in_min = array[i];
        else if (in_max < array[i])
                in_max = array[i];
    }
    // Обозначим min и max потенциальные
    // мин и макс массива B
    min = in_max - K;
    max = in_min + K;
// Возможных массивов B всего 2^N
// мы ищем минимальную возможную разницу между мин и макс
// Гарантированная разница - та, которая была (сдвинулся весь массив на K)
// Минимальная возможная (теоретически) разница = max - min - 2k
// То есть все элементы остались между новыми max и min
// ищем разницу наиболее приближенную к минимальной возможной
        // Если после изменения min и max поменялись, переставим их местами
    if (max < min) {
        i   = max;
        max = min;
        min = i;
    }
        // Проходим по всему циклу
    for (i = 0 ; i < N; ++i) {
        // Если i-ый нельзя изменить так, чтобы не испортить максимум или минимум
        // Если он допустим не портит минимум, но перепрыгивает новый максимум,
        // то мы проигнорируем его, так как ищем миним разницу
        if (array[i] + K > max && array[i] - K < min) {
            // Пытаемся понять к чему этот элемент ближе,
            // чтобы минимально изменить разницу
            if (array[i] + K - max < min - array[i] + K)
                max = array[i] + K;
            else
                min = array[i] - K;
        }
    }

    // Если у нас получилось, что max - min (потенциально возможная разница) меньше, чем
    // изначальная разница in_max-in_min
    if ((max - min) < (in_max - in_min))
        return (max - min);
    else
        return (in_max - in_min);
}
int fill_array(FILE* inp, int* array, int N)  {
    for (int i = 0; i < N; i++) {
        if (fscanf(inp, "%d", &(array[i])) != 1) {
            printf("Not enough data!\n");
            return -1;
        }
    }
    return 1;
}
void print_array(int* array, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    FILE* inp;
    int* array;
    int N = 0;
    int K = 0;
    // Открываем файл
    inp = fopen("input.txt", "r");
    // Если не открылся, то печатаем ошибку и выходим
    if (!inp) {
        printf("Error reading file!\n");
        return -1;
    }
    // Считываем первые два числа из файла,
    if (fscanf(inp, "%d%d", &N, &K) != 2) {
    // Если не получается считать, то значит, что
    // либо там не целое число, либо там пусто
        printf("File is empty or wrong input!\n");
        fclose(inp);
        return -1;
    }

    // Выделяем память для нашего массива
    array = (int*)malloc(N*sizeof(int));
    // Если не получилось, возвращаем ошибку
    if (!array) {
        printf("Error in malloc\n");
        fclose(inp);
        return -1;
    }

        // Заполняем массив из файла
    // Если не получилось заполнить, то есть
    // в файле меньше элементов, чем в размере
    // возвращаем ошибку
    if (fill_array(inp, array, N) < 0) {
        free(array);
        fclose(inp);
        return -1;
    }

    printf("%d\n", Process(array, N, K));

    free(array);
    fclose(inp);
    return 0;
}
