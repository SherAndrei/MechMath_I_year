/*
    Проверить есть ли в последовательности участок:
    возрастание, постоянство, убывание
*/
#include <stdio.h>

int main() {
    FILE* input;
    int current = 0, last = 0;
    // flags:
    int is_increasing = 0, is_constant = 0;
    // final flag:
    int is_there_sequence = 0;

    if ((input = fopen("input.txt", "r")) == NULL) {
        printf("Error reading file\n");
        return -1;
    }

    // считаем первый элемент:
    if (fscanf(input, "%d", &last) != 1) {
        printf("File is empty!\n");
        return -1;
    }

    // работаем с остальной последовательностью
    while (fscanf(input, "%d", &current) == 1) {
        if (last < current) {
            is_increasing = 1;
            last = current;
            continue;
        }
        if (is_increasing && last == current) {
            is_constant = 1;
            last = current;
            continue;
        } else {
            is_increasing = 0;
        }
        if (is_constant && last > current) {
            is_there_sequence = 1;
            last = current;
            continue;
        } else {
            is_increasing = 0;
            is_constant = 0;
        }

        last = current;
    }
    if (is_there_sequence)
        printf("Yes!\n");
    else
        printf("No!\n");
}
