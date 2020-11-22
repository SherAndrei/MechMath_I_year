#include <stdio.h>

// Получаем число на вход
// Рассматриваем его побитово
// Рассматриваем если есть бит и через один такой же, то между ставим 1

unsigned function(unsigned X) {
    int flag_first, flag_second;
    for (int i = sizeof(int)*8 - 1; i >= 0; i -= 2) {
        flag_first  = (X & (1u << i))       ? 1 : 0;
        flag_second = (X & (1u << (i - 2))) ? 1 : 0;
        if ((flag_second && flag_first) || (!flag_first && !flag_second)) {
            X |= (1u << (i - 1));
        }
    }
    return X;
}


void showbits(unsigned X) {
    for (int i = sizeof(int)*8 - 1; i >= 0; --i) {
        putchar((X & (1u << i)) ? '1' : '0');
    }
    putchar('\n');
}

int main() {
    unsigned X;
    scanf("%u", &X);
    showbits(X);
    X = function(X);
    showbits(X);
    printf("%u\n", X);
}
