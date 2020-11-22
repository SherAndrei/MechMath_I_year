// Найти максимальное расстояние между единицами
// в побитовом представлении числа
#include <stdio.h>

// 1001
int find_max_distance(unsigned int x) {
    int count_zeroes = 0, max = 0;
    int is_last_zero = 0;
    for (int i = sizeof(int) * 8 - 1; i >= 0; ++i) {
        if (x & (1 << i)) {
            if (is_last_zero)
                max = count_zeroes;
            is_last_zero = 0;
            count_zeroes = 0;
        } else {
            count_zeroes++;
            is_last_zero = 1;
        }
    }
}

int main()  {
    char i = 0;
    while ((i = getchar()) != EOF) {
        printf("%c", i);
    }
    printf("Done\n");
}
