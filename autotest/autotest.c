#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define a(i, j, Columns) A[(i)*(Columns)+(j)]

int lentgh(FILE*f);
double *scanarray(FILE*f);
void prn(double *A, int Strings, int Columns, FILE*f);
void mult(double *A, int Strings, int Columns, FILE*f);

int main(void) {
    int k = 0, Columns = 0, Strings = 0;
    double *A, raznost = 0;
    FILE*inp, *out;

    inp = fopen("input.txt", "r");
    out = fopen("output.txt", "w");
    if (!inp)
        return -1;

    if (fscanf(inp, "%d %d ", &Strings, &Columns) != 2)
        return -1;

    if (Columns*Strings == 0)
        return -1;

    k = lentgh(inp);
    if (k != (Columns*Strings))
        return -1;

    A = scanarray(inp);

    for (int i = 0; i < Columns; i++) {
        for (int j = 1; j < Columns; j++) {
            for (int p= 0; p < Strings; p++) {
                raznost = raznost + A[(p)*(Columns)+(j)]-A[(p)*(Columns)+((j)-(1))];
            }
            if (raznost< 0) {
                for (int t = 0; t < Strings; t++) {
                    double temp;
                    temp = A[(t)*(Columns) + (j)];
                    A[(t)*(Columns) + (j)] = A[(t)*(Columns)+((j)-(1))];
                    A[(t)*(Columns) + ((j)-(1))] = temp;
                }
            }
            raznost = 0;
        }
    }

    prn(A, Strings, Columns, out);
    fprintf(out, "\n");
    mult(A, Strings, Columns, out);
    return 0;
}

int lentgh(FILE*f) {
    int k = 0;
    double g;
    while (fscanf(f, "%lf", &g) == 1) {
            k++;
        }
    rewind(f);
    return k;
}

double *scanarray(FILE*f) {
    int p, t, i = 0;
    double *A;
    fscanf(f, "%d %d", &p, &t);
    A = (double*)malloc(p*t*sizeof(double));
    while (fscanf(f, "%lf ", &A[i]) == 1)
        i++;
    return A;
}

void prn(double *A, int Strings, int Columns, FILE*f) {
    fprintf(f, "%d %d\n", Strings, Columns);
    for (int i = 0; i < Strings; i++) {
        for (int j = 0; j < Columns; j++) {
            fprintf(f, "%lf ", a(i, j, Columns));
        }
        fprintf(f, "\n");
    }
}

void mult(double *A, int Strings, int Columns, FILE *f) {
    double mult = 0;
    for (int i = 0; i < Strings; i++) {
        for (int j = 0; j < Columns; j++) {
            mult+=A[(i)*(Columns)+j]*A[(Strings-1)*(Columns)+j];
        }
        fprintf(f, "%lf ", mult);
        mult = 0;
    }
}
