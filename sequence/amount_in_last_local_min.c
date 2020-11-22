/*
Локальным минимумом последовательности {ai}, i = 1,...,N
называется подпоследовательность данной
последовательности {aj}, j =k,...,l, элементы которой равны
между собой и для которых выполняются соотношения:
 a) k = 1 или ak−1 > ak; b) l = N или al+1 > al

Требуется за один проход по файлу и без
запоминания последовательности в массиве
определить требуемую характеристику последовательности:
Количество элементов последовательности в последнем
локальном минимуме последовательности.
*/

#include <stdio.h>

int Process(FILE* inp)  {
    double last = 0., current = 0.;
    // Флажок чтобы отработать случай, когда последовательность только неубывает
    int is_increasing = 0;
    // Чтобы не проверять случай, когда элемент в последовательности 1
    int final_amount = 1;

    // Считаем первый элемент, записав его в last
    if (fscanf(inp, "%lf", &last) != 1) {
        return 0;  // Значит файл пустой или некорректные данные
    }
    // Работаем теперь с остальной последовательностью
    while (fscanf(inp, "%lf", &current) == 1) {
        if (last > current) {
            is_increasing = 0;
            final_amount = 1;
            last = current;
        } else if (last == current) {
            final_amount++;
            if (is_increasing)
                final_amount = 1;
            last = current;
        } else {
            last = current;
            is_increasing = 1;
        }
    }
    return final_amount;
}

int main() {
    FILE* inp;
    int result = 0;
    inp = fopen("input.txt", "r");
    if (!inp) {
        printf("Error reading file!\n");
        return -1;
    }

    result = Process(inp);
    printf("%d\n", result);
}
