// Дано целое число X. Требуется
// инвертировать все биты в его двоичном представлении кроме
// лидирующих нулей.
#include <stdio.h>

unsigned int invert(unsigned int X)  {
    unsigned int result = 0;
    int count_lead_zeroes = 0;
    // Чтобы не обращать внимание на лидирующие нули
    // заведем флажок, который нам подскажет, что
    // лидирущие нули кончились
    int is_first_one_found = 0;
    // Идем по битовому представлению слева, пока не натыкаемся
    // на единичку, одновременно считаем сколько у нас лидирующих нулей
    for (int i = sizeof(int)*8 - 1; i >= 0; --i) {
        if ((X & (1 << i)) == 0) {
            if (!is_first_one_found)
                count_lead_zeroes++;
        } else {
            is_first_one_found = 1;
            // Каждый раз когда натыкаемся на единичку ставим ее на
            // противоположное место в результате
            result |= (1 << (31 - i));
        }
    }
    // затем убираем образовавшиеся нули справа
    result >>= count_lead_zeroes;
    return result;
}

int main() {
    unsigned int X;
    while (1)  {
        printf("Enter your number:\n");
        scanf("%u", &X);
        printf("%u\n", invert(X));
    }
}