#include <stdio.h>

void showbits(int x) {
    for (int i = (sizeof(int) * 8) - 1; i >= 0; i--) {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

int main()  {
    int num;
    while (1) {
        printf("Enter your number:\n");
        if (scanf("%d", &num) != 1) {
            printf("Not a number!\n");
            return 1;
        }
        showbits(num);
    }
}
