#include <stdio.h>

#define MAX_SIZE 100

// Функция для сравнения двух чисел: возвращает 1 если A > B, -1 если A < B, 0 если A == B
int compare_arrays(const int *a, int a_len, const int *b, int b_len) {
    if (a_len > b_len) return 1;
    if (a_len < b_len) return -1;
    
    // Если длины равны, сравниваем поразрядно от старшего к младшему
    for (int i = 0; i < a_len; i++) {
        if (*(a + i) > *(b + i)) return 1;
        if (*(a + i) < *(b + i)) return -1;
    }
    return 0;
}

// Функция сложения: R = A + B
int add_arrays(const int *a, int a_len, const int *b, int b_len, int *r) {
    int i = a_len - 1;
    int j = b_len - 1;
    int k = 0; // Индекс в результирующем массиве (заполняем с конца)
    int carry = 0;

    // Складываем в столбик, начиная с младших разрядов
    while (i >= 0 || j >= 0 || carry > 0) {
        if (k >= MAX_SIZE + 1) return 0; // Переполнение максимального размера + 1 для переноса

        int sum = carry;
        if (i >= 0) {
            sum += *(a + i);
            i--;
        }
        if (j >= 0) {
            sum += *(b + j);
            j--;
        }

        *(r + k) = sum % 10;
        carry = sum / 10;
        k++;
    }
    return k; // Возвращаем реальную длину результата
}

// Функция вычитания: R = A - B (вызывается только если A >= B)
int sub_arrays(const int *a, int a_len, const int *b, int b_len, int *r) {
    int i = a_len - 1;
    int j = b_len - 1;
    int k = 0;
    int borrow = 0;

    while (i >= 0) {
        int diff = *(a + i) - borrow;
        i--;

        if (j >= 0) {
            diff -= *(b + j);
            j--;
        }

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        *(r + k) = diff;
        k++;
    }

    // Убираем ведущие нули (кроме последней единичной цифры, если результат 0)
    while (k > 1 && *(r + k - 1) == 0) {
        k--;
    }
    return k;
}

// Вспомогательная функция для вывода перевернутого массива (так как считали с конца)
void print_result(const int *r, int len) {
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", *(r + i));
    }
    printf("\n");
}

int main() {
    int a[MAX_SIZE], b[MAX_SIZE];
    int a_len = 0, b_len = 0;
    char ch;

    // Считываем первое число посимвольно
    while (scanf("%c", &ch) == 1 && ch != '\n') {
        if (ch >= '0' && ch <= '9') {
            if (a_len >= MAX_SIZE) { printf("n/a\n"); return 0; }
            *(a + a_len) = ch - '0';
            a_len++;
        } else {
            printf("n/a\n");
            return 0;
        }
    }

    // Считываем второе число посимвольно
    while (scanf("%c", &ch) == 1 && ch != '\n' && ch != '\0') {
        if (ch >= '0' && ch <= '9') {
            if (b_len >= MAX_SIZE) { printf("n/a\n"); return 0; }
            *(b + b_len) = ch - '0';
            b_len++;
        } else {
            printf("n/a\n");
            return 0;
        }
    }

    // Валидация: пустой ввод недопустим
    if (a_len == 0 || b_len == 0) {
        printf("n/a\n");
        return 0;
    }

    int res_add[MAX_SIZE + 1];
    int res_sub[MAX_SIZE];

    // 1. Сложение
    int add_len = add_arrays(a, a_len, b, b_len, res_add);
    if (add_len == 0) {
        printf("n/a\n");
    } else {
        print_result(res_add, add_len);
    }

    // 2. Вычитание
    int cmp = compare_arrays(a, a_len, b, b_len);
    if (cmp < 0) {
        // Уменьшаемое меньше вычитаемого (A < B)
        printf("n/a\n");
    } else {
        int sub_len = sub_arrays(a, a_len, b, b_len, res_sub);
        print_result(res_sub, sub_len);
    }

    return 0;
}
