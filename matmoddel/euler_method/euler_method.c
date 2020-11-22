/*
Численно найдите приближенное решение дифференциального уравнения
y'(x) = −ay(x) на отрезке [0, 1] при начальном условии y(0) = 1,
используя неявный метод Эйлера:
y_{k+1} = y_{k} − hay_{k+1}, k = 0, 1,..., N − 1; y0 = y(x0)
Сравните с точным решением y(x) = e^{−ax} для a = 10, 1000
при N = 1, 10, 100, 1000, 10000.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_data(FILE* out, double a, int N) {
    double x0 = 0., y0 = 1.;
    double h = (1. - 0.) / N;
    fprintf(out, "%lf %.15lf\n", x0, y0);
    // y_{k+1}+ahy_{k+1} = yk
    for (int k = 0;  k < N; k++) {
        y0 /= (1 + h*a);
        x0 += h;
        fprintf(out, "%lf %.15lf\n", x0, y0);
    }
}

int main() {
    FILE* file;
    char filename[20];
    for (int i = 0, N = 1; i < 4; i++, N *= 10) {
        snprintf(filename, sizeof(filename), "input%d.txt", i);
        file = fopen(filename, "w");
        print_data(file, 10, N);
        fclose(file);
    }
    for (int i = 4, N = 1; i < 8; i++, N *= 10) {
        snprintf(filename, sizeof(filename), "input%d.txt", i);
        file = fopen(filename, "w");
        print_data(file, 1000, N);
        fclose(file);
    }
}