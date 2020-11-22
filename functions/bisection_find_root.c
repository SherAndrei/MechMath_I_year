#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double F(double x)  {
    return x*x*x - x*x - 1;
}

double find_root(double a, double b, double eps, int* flag, int N) {
    int counter = 1;
    double r = 0;
    double l1 = a, l2 = b;
    double f1, f2, f3;
    if (F(a) == 0) {
        return a;
    } else if (F(b) == 0) {
        return b;
    } else {
        while (counter < N) {
            f1 = F(l1);
            r = (l1 + l2) / 2.;
            f2 = F(r);
            f3 = F(l2);

            if (fabs(f2) < eps) {
                *flag = 1;
                break;
            }
            if (f1 * f2 < 0)
                l2 = r;
            else if (f2 * f3 < 0)
                l1 = r;
            counter++;
        }
    }
    return r;
}

int main() {
    FILE* out = fopen("result.txt", "w");
    double a, b, eps, x;
    int n = 0, flag = 0;
    scanf("%lf%lf%lf%d", &a, &b, &eps, &n);
    x = find_root(a, b, eps, &flag, n);
    if (flag)
        fprintf(out, "x = %lf\nf(x) = %e\na = %lf\nb = %lf\neps = %e\n", x, F(x), a, b, eps);
    else
        fprintf(out, "Error\n");
}
