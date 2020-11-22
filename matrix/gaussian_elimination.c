#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// храним матрицу в одномерном массиве по строкам
#define M(i, j, n) matrix[((i)*(n) + j)]
#define Err(i, j, n) eps[(i)*(n)+(j)]
// храним матрицу в одномерном массиве по столбцам
// #define M(i, j, n) matrix[((j)*(n) + i)]
// #define Err(i, j, n) eps[(j)*(n)+(i)]

// Считываем первый элемент с файла (размерность) и возвращаем его
int get_dim(FILE* input) {
    int result = 0;

    if (fscanf(input, "%d", &result) && result > 0)
        return result;
    return -1;
}
// Создаем и заполняем массив, возвращаем указатель на его первый элемент
double* create_array(FILE* input, int num_of_elems) {
    double* array = (double*)malloc(num_of_elems * sizeof(double));
    for (int i = 0; i < num_of_elems; ++i)
        fscanf(input, "%lf", &(array[i]));
    return array;
}
// Создаем и заполняем массив погрешностей, возвращаем указатель на его первый элемент
double * create_err(double * array, int num_of_elems) {
    double* eps = (double*)malloc(num_of_elems*sizeof(double));
    for (int i = 0; i < num_of_elems; i++)
        eps[i] = fabs(array[i])*1e-15;
    return eps;
}

// Печатаем массив
void print_matrix(double* matrix, int dim) {
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j)
            printf("%.5lf ", M(i, j, dim));

        printf("\n");
    }
    printf("\n\n");
}
// печатаем ответ
void print_answer(double* answer, int dim) {
    for (int i = 0; i < dim; ++i)
        printf("%.5f ", answer[i]);
    printf("\n");
}

// Преобразование Гаусса
double gaussian_elimination(double* matrix, double* eps, double* answer, double* answ_eps, int dim) {
    int i, j, l, nmax;
    double Max, c, temp;
    double sum;
    // проходим по столбцам
    for (j = 0; j < dim; j++) {
        // сначала назначаем максимальным элементом a_(j, j)
        Max = fabs(M(j, j, dim));
        // строку с максимльным элементом называем nmax
        nmax = j;

        // идем вниз по столбцу
        for (i = j; i < dim; i++)    {
            // если находим какой-то, который больше Max, то назначаем его максимальным элементом
            if (fabs(M(i, j, dim)) > Max) {
                nmax = i;
                Max = M(i, j, dim);
            }
        }

        // меняем j-ую строчку на строчку с максимальным элементом
        for (i = j; i < dim; i++) {
            // меняем начальную матрицу
            temp            = M(j, i, dim);
            M(j, i, dim)    = M(nmax, i, dim);
            M(nmax, i, dim) = temp;

            // меняем матрицу погрешностей
            temp = Err(j, i, dim);
            Err(j, i, dim) = Err(nmax, i, dim);
            Err(nmax, i, dim) = temp;
        }

        // меняем правую часть
        temp         = answer[j];
        answer[j]    = answer[nmax];
        answer[nmax] = temp;
        // меняем погрешности правой части
        temp           = answ_eps[j];
        answ_eps[j]    = answ_eps[nmax];
        answ_eps[nmax] = temp;

        // вычитаем из всех строчек строчку с максимальным элементом,
        // умноженную на соответствующий коэфф c, чтобы получить нули в столбце
        for (i = j + 1; i < dim; i++) {
            c = M(i, j, dim)/M(j, j, dim);

            for (l = j; l < dim; l++) {
                M(i, l, dim)   -= c*M(j, l, dim);
                Err(i, l, dim) += fabs(c)*Err(j, l, dim);
            }
            answer[i]   -= c*answer[j];
            answ_eps[i] += fabs(c)*answ_eps[j];
        }
    }


    // Матрица уже верхнедиагональная, если что-то на диагонали 0, то матрица вырождена
    for (i = 0; i < dim; i++) {
        if (fabs(M(i, i, dim)) < Err(i, i, dim))
            return 1;
    }
    // Матрица уже верхнедиагональная и невырожденная, считаем ответ и записываем его в правую часть
    for (i = dim - 1; i >= 0; --i) {
        sum = 0;
        for (j = i + 1; j < dim; ++j)
            sum += answer[j] * M(i, j, dim);

        // так как мы перезаписываем все в правую часть
        if (fabs(answer[i]) < answ_eps[i])
            answer[i] = 0.0;
        else
            answer[i] = (answer[i] - sum) / M(i, i, dim);
    }

    return 0;
}

int main() {
    FILE* input;
    input = fopen("input.txt", "r");

    int dim = get_dim(input);

    double* matrix     = create_array(input, dim * dim);
    double* matrix_eps = create_err(matrix, dim * dim);
    print_matrix(matrix, dim);

    double* answer     = create_array(input, dim);
    double* answer_eps = create_err(answer, dim);
    print_answer(answer, dim);
//    gaussian_elimination(matrix, matrix_eps, dim);
    int error = gaussian_elimination(matrix, matrix_eps, answer, answer_eps, dim);

    print_matrix(matrix, dim);
    if (error)
        printf("Matrix is degenerate!\n");
    else
        print_answer(answer, dim);

    free(matrix);
    free(matrix_eps);
    free(answer);
    free(answer_eps);
    fclose(input);
    return 0;
}
