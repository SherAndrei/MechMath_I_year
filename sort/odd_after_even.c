/*
Дан массив A из 2N неотрицательных целых чисел. Половину
элементов в массиве A составляют чётные числа,
а оставшуюся половину — нечётные. Отсортируйте
массив таким образом, чтобы элемент A[i] был
чётным, если i — чётное и нечётным в противном
случае. Подойдёт любой вариант, удовлетворяющий
 данному условию
*/
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int odd(int number)  {
    if (number % 2 == 1)
        return 1;
    return 0;
}
int even(int number) {
    if (number % 2 == 0)
        return 1;
    return 0;
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

void sort(int* array, int N)  {
    // Идея:
    // будем идти по четным позициям с помощью i
    // по нечетным с помощью j
    // и будем их сравнивать
    int i = 0, j = 1;

    while (1) {
        // Находим следующую позицию, на которой
        // на i-ом месте в массиве стоит нечетное число
        while (i < N && even(array[i]))
            i += 2;
        // Аналогично находим следующую позицию, на которой
        // на j-ом месте в массиве стоит четное число
        while (j < N && odd(array[j]))
            j += 2;
        // Поменяем теперь то, что находится на i и j месте в массиве
        // Если какое-то из условий ниже нарушено, то массив уже готов
        if (i < N && j < N) {
            swap(&(array[i]), &(array[j]));
        } else {
            break;
        }
    }
}

int main()  {
    FILE* inp;
    int* array;
    int N = 0;
    // Открываем файл
    inp = fopen("input.txt", "r");
    // Если не открылся, то печатаем ошибку и выходим
    if (!inp) {
        printf("Error reading file!\n");
        return -1;
    }
    // Считываем первое число из файла,
    if (fscanf(inp, "%d", &N) != 1) {
    // Если не получается считать, то значит, что
    // либо там не целое число, либо там пусто
        printf("File is empty or wrong input!\n");
        fclose(inp);
        return -1;
    }

    // Если нам дали неправильный размер, то сворачиваемся
    if (N % 2 != 0) {
        printf("Wrong input! Size is odd! Must be even\n");
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

    // Посмотрим что получилось
    printf("Before: ");
    print_array(array, N);
    // Сортируем
    sort(array, N);
    // Посмотрим что получилось после сортировки
    printf("After : ");
    print_array(array, N);

    free(array);
    fclose(inp);
    return 0;
}
