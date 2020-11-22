/*
Единый массив для всех элементов матрицы (функция получает аргумент double* matr)

Напишите программу, считывающую m×n матрицу A,
вычисляющую B = (A^T)A и произведение
строки матрицы B с наибольшей векторной нормой
||x||_{inf} = max_{i = 1,...,m} |x_i|
на её столбец с наименьшей векторной нормой
|x||_{2} = sqrt{(sum^m_{i = 1} x_i^2)/m}
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// m - количество строчек
// n - количество столбцов

void print(double* matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", matrix[i*n + j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

double* alloc(int size) {
    return (double*)calloc(size, sizeof(double));
}

// Наибольшая векторная форма строки i в matrix размера m*n
double max_vector_norm(double* matrix, int i, int n) {
    double max = matrix[i*n + 0];
    for (int j = 1; j < n; j++) {
        if (max < matrix[i*n + j])
            max = fabs(matrix[i*n + j]);
    }
    return max;
}

// Наименьшая векторная форма столбца j в matrix размера m*n
double min_vector_norm(double* matrix, int j, int m, int n) {
    double result = 0.;
    for (int i = 0; i < m; i++) {
        result += (matrix[i * n + j] * matrix[i * n + j]);
    }
    return sqrt(result / m);
}
// Allocates third matrix m1*n2
double* multiply(double* matrix1, int m1, int n1,
                 double* matrix2, int m2, int n2) {
    if (m2 != n1) {
        printf("Cannot multiply!\n");
        return NULL;
    }
    double* result;
    if ((result = (double*)calloc(m1 * n2, sizeof(double))) == NULL) {
        printf("Cannot malloc!\n");
        return NULL;
    }

    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n2; j++)
            for (int k = 0; k < n1; k++)
                result[i*n2+j] += matrix1[i*n1 + k] * matrix2[k*n2 + j];

    return result;
}

// Allocates transposed matrix
double* traspose(double* matrix, int m, int n) {
    double* t_matrix;
    if ((t_matrix = (double*)calloc(n * m, sizeof(double))) == NULL) {
        printf("Cannot malloc!\n");
        return NULL;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            t_matrix[j*m + i] = matrix[i*n + j];

    return t_matrix;
}

int find_row_with_max_vec_norm(double* matrix, int m, int n)  {
    double max_vn = max_vector_norm(matrix, 0, n);
    double temp = 0.;
    int max = 0;

    for (int i = 0; i < m; i++) {
        temp = max_vector_norm(matrix, i, n);
        if (max_vn < temp) {
            max_vn = temp;
            max  = i;
        }
    }

    return max;
}
int find_col_with_min_vec_norm(double* matrix, int m, int n) {
    double min_vn = min_vector_norm(matrix, 0, m, n);
    double temp = 0.;
    int min = 0;

    for (int j = 0; j < m; j++) {
        temp = min_vector_norm(matrix, j, m, n);
        if (temp < min_vn) {
            min_vn = temp;
            min  = j;
        }
    }

    return min;
}

double answer(double* matrix, int dim, int i_max, int j_min) {
    double result = 0.;

    for (int k = 0; k < dim; k++)
        result += matrix[i_max*dim + k] * matrix[k*dim + j_min];

    return result;
}

int main() {
    FILE* inp;
    double* matrix;
    double* t_matrix;
    double* result;
    int m, n;
    if ((inp = fopen("input.txt", "r")) == NULL) {
        printf("Error file!\n");
        return -1;
    }

    if (fscanf(inp, "%d%d", &m, &n) != 2) {
        printf("Error dimensions!\n");
        fclose(inp);
        return -1;
    }

    if ((matrix = alloc(m*n)) == NULL) {
        printf("Error alloc!\n");
        fclose(inp);
        return -1;
    }

    for (int i = 0; i < m * n; i++) {
        if (fscanf(inp, "%lf", &matrix[i]) != 1) {
            printf("Error input!\n");
            free(matrix);
            fclose(inp);
            return -1;
        }
    }

    t_matrix = traspose(matrix, m, n);
    result   = multiply(t_matrix, n, m, matrix, m, n);

    int i_max = find_row_with_max_vec_norm(result, n, n),
        j_min = find_col_with_min_vec_norm(result, n, n);

    print(result, n, n);
    printf("%lf\n", answer(result, n, i_max, j_min));

    free(matrix);
    free(t_matrix);
    free(result);
    fclose(inp);
}
