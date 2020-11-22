#include <stdio.h>

int main() {
    unsigned long long result = 0;
    char current_bit = 0;
    printf("Enter your bits:\n");
    while ((current_bit = getchar() ) != EOF) {
        if (current_bit == '1') {
            result <<= 1;
            result |= 1;
        } else if (current_bit == '0') {
            result <<= 1;
        }
    }
    printf("%llu\n", result);

}