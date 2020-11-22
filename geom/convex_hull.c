/*
В следующих задаче предполагается, что в файле записано
несколько пар чисел, которые можно рассматривать как
координаты множества точек на плоскости.
Дано множество точек на плоскости.
Построить выпуклую оболочку этого множества.
Выпуклая оболочка печатается в файл output.txt.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159

// Считываем количество точек
int get_amount(FILE* inp) {
    int count = 0;
    double temp1, temp2;
    while (fscanf(inp, "%lf%lf", &temp1, &temp2) == 2)
        count++;

    // Возвращаем каретку в файле на начало
    rewind(inp);
    return count;
}



// Структура точки для задачи
struct Point {
    double x;
    double y;
};
typedef struct Point POINT;
// переопределение типа struct Point в POINT для удобства

void print_array(POINT* array, int N) {
    FILE* out;
    out = fopen("output.txt", "w");
    for (int i = 0; i < N; ++i) {
        fprintf(out, "%lf %lf\n", array[i].x, array[i].y);
    }
    fclose(out);
}

// Глобальная переменная - точка - которая понадобится для
// сравнения в функции qsort
POINT p0;

// Вспомогательная функция, чтобы поменять точки местами
void swap(POINT* lhs, POINT* rhs) {
    POINT temp = *lhs;
          *lhs = *rhs;
          *rhs = temp;
}
// Вспомогательная функция, возвращающая квадрат
// расстояния между двумя точками
double distance(POINT p1, POINT p2) {
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
// Чтобы найти ориентацию тройки (p, q, r).
int orientation(POINT p, POINT q, POINT r) {
    double val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);
    if     (val == 0.) return 0;  // Коллинеарны
    else if (val > 0.) return 1;  // По часовой
    else               return 2;  // Против часовой
}
// Функция, предназначеная для библиотечной функции qsort(),
// чтобы отсортировать массив точек относительно первой точки
int compare(const void *vp1, const void *vp2) {
    POINT *p1 = (POINT *)vp1;
    POINT *p2 = (POINT *)vp2;
    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0) {
       if (distance(p0, *p1) <= distance(p0, *p2)) {
            return 1;
       } else {
            return -1;
       }
    }
    if (o == 2)
        return -1;
    else
        return 1;
}

POINT* convex_hull(POINT* points, int *Np)  {
    int N = *Np, min = 0;
    double ymin = points[0].y;
    double y;
    POINT* stack;

    for (int i = 1; i < N; i++) {
        y = points[i].y;
        // Выберем самую нижную левую точку
        // в случае если их несколько
        if ((y < ymin) || (ymin == y &&
            points[i].x < points[min].x)) {
                ymin = points[i].y;
                min = i;
            }
    }

    // Поместим полученную точку в самое начало массива
    swap(&(points[0]), &(points[min]));
    // Отсортируем n-1 точку относительно первой точки.
    // Точка p1 идет перед точкой p2 в остортированном массиве,
    // если p2 имеет бОльший полярный угол (в направлении
    // против часовой стрелки), чем p1
    p0 = points[0];
    qsort(&points[1], N-1, sizeof(POINT), compare);

    // Если две или больше точек образуют одинаковый угол с p0,
    // Уберем все, кроме той, которая дальше всех от p0,
    // Не забываем, что при сортировке, наш критерий был
    // держать дальнюю точку в конце, когда больше одной точки
    // образуют одинаковый угол

    int m = 1;  // Размер модифицированного массива
    for (int i = 1; i < N; i++) {
        // Убираем i пока угол i и i+1 одинаков
        // относительно p0
        while (i < N - 1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        points[m] = points[i];
        m++;  // Обновляем размер нового массива
    }
    // Изменим размеры старых массивов на новый
    *Np = N = m;
    // Если модицированный массив имеет меньше трех точек
    // то построить выпуклую оболочку невозможно
    if (N < 3) return points;
    // Создаем пустой массив и инициализируем первые три элемента
    stack = (POINT*)malloc(N*sizeof(POINT));
    stack[0] = points[0];
    stack[1] = points[1];
    stack[2] = points[2];

    // Переменная, которая позволит нам двигаться по stack сначала
    m = 2;
    // Обрабатываем остальные n-3 точки
    for (int i = 3; i < N; i++) {
        // Продолжаем убирать крайние точки, пока угол
        // сформированный точками m-1, m и points[i]
        // не сделает нелевый поворот
        while (orientation(stack[m-1], stack[m], points[i]) != 2)
            m--;
        // на m элемент вставляем подходящую точку
        ++m;
        stack[m] = points[i];
    }
    *Np = ++m;
    free(points);
    return stack;
}

int main() {
    FILE* inp;
    int amount_of_points;
    POINT* points, *c_hull;

    // Открываем файл на чтение
    inp = fopen("input.txt", "r");
    if (!inp) {
        printf("Error in file\n");
        return -1;
    }

    // Создаем массив из наших точек длиной, которую получили в функции get_amount
    amount_of_points = get_amount(inp);
    points = (POINT*)malloc(amount_of_points*sizeof(POINT));
    if (!points) {
        printf("Error in malloc\n");
        fclose(inp);
        return -1;
    }

    // Заполняем наш массив
    for (int i = 0; i < amount_of_points; i++) {
        if (fscanf(inp, "%lf%lf", &(points[i].x), &(points[i].y)) != 2) {
            printf("Wrong input\n");
            free(points);
            fclose(inp);
            return -1;
        }
    }

    // Передаем по ссылке, чтобы потом использовать при печати правильное количество
    c_hull = convex_hull(points, &amount_of_points);
    print_array(c_hull, amount_of_points);

    free(c_hull);
    fclose(inp);
}
