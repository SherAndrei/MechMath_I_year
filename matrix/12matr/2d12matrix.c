/*
Набор массивов-строк с массивом указателей на каждую строку
(функция получает аргумент double** matr)

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

void print(double** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2lf ", matrix[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

double** alloc_m(int m, int n) {
    double** result;
    result = (double**)malloc(m * n * sizeof(double*));
    for (int i = 0; i < m; i++)
        result[i] = (double*)calloc(n, sizeof(double));

    return result;
}
void free_m(double** matrix, int m) {
    for (int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
}

// Наибольшая векторная форма строки i в matrix размера m*n
double max_vector_norm(double** matrix, int i, int n) {
    double max = matrix[i][0];
    for (int j = 1; j < n; j++) {
        if (max < matrix[i][j])
            max = matrix[i][j];
    }
    return max;
}

// Наименьшая векторная форма столбца j в matrix размера m*n
double min_vector_norm(double** matrix, int j, int m) {
    double result = 0.;
    for (int i = 0; i < m; i++) {
        result += (matrix[i][j] * matrix[i][j]);
    }
    return sqrt(result / m);
}
// Allocates third matrix m1*n2
double** multiply(double** matrix1, int m1, int n1,
                  double** matrix2, int m2, int n2) {
    if (m2 != n1) {
        printf("Cannot multiply!\n");
        return NULL;
    }
    double** result = alloc_m(m1, n2);

    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n2; j++)
            for (int k = 0; k < n1; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    return result;
}

// Allocates transposed matrix
double** traspose(double** matrix, int m, int n) {
    double** t_matrix = alloc_m(n, m);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            t_matrix[j][i] = matrix[i][j];

    return t_matrix;
}

int find_row_with_max_vec_norm(double** matrix, int m, int n)  {
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
int find_col_with_min_vec_norm(double** matrix, int m) {
    double min_vn = min_vector_norm(matrix, 0, m);
    double temp = 0.;
    int min = 0;

    for (int j = 0; j < m; j++) {
        temp = min_vector_norm(matrix, j, m);
        if (min_vn < temp) {
            min_vn = temp;
            min  = j;
        }
    }

    return min;
}

double answer(double** matrix, int dim, int i_max, int j_min) {
    double result = 0.;

    for (int k = 0; k < dim; k++)
        result += matrix[i_max][k] * matrix[k][j_min];

    return result;
}

int main() {
    FILE* inp;
    double** matrix;
    double** t_matrix;
    double** result;
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

    if ((matrix = alloc_m(m, n)) == NULL) {
        printf("Error alloc!\n");
        fclose(inp);
        return -1;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (fscanf(inp, "%lf", &(matrix[i][j])) != 1) {
                printf("Error input!\n");
                free_m(matrix, m);
                fclose(inp);
                return -1;
            }
        }

    t_matrix = traspose(matrix, m, n);
    result   = multiply(t_matrix, n, m, matrix, m, n);

    int i_max = find_row_with_max_vec_norm(result, n, n),
        j_min = find_col_with_min_vec_norm(result, n);

    print(result, n, n);
    printf("%lf\n", answer(result, n, i_max, j_min));

    free_m(matrix, m);
    free_m(t_matrix, n);
    free_m(result, n);
    fclose(inp);
}
