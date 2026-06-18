#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define SAMPLES 42

int main() {
    double start = -PI;
    double end = PI;
    double step = (end - start) / (SAMPLES - 1);

    for (int i = 0; i < SAMPLES; i++) {
        double x = start + i * step;

        // 1. Первая колонка: значение x
        printf("%.7f|", x);

        // 2. Вторая колонка: Верзьера Аньези (диаметр d = 1)
        double y1 = 1.0 / (1.0 + x * x);
        printf("%.7f|", y1);

        // 3. Третья колонка: Лемниската Бернулли (Y > 0)
        double lemniscate_inner = sqrt(4.0 * x * x + 1.0) - x * x - 1.0;
        if (lemniscate_inner >= 0.0) {
            double y2 = sqrt(lemniscate_inner);
            printf("%.7f|", y2);
        } else {
            printf("-|");
        }

        // 4. Четвертая колонка: Квадратичная гипербола
        if (x != 0.0) {
            double y3 = 1.0 / (x * x);
            printf("%.7f", y3);
        } else {
            printf("-");
        }

        printf("\n");
    }

    return 0;
}
