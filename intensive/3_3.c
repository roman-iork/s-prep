#include <stdio.h>

long long fibonacci(int n);

int main() {
    int n;
    char term;

    if (scanf("%d%c", &n, &term) != 2 || term != '\n' || n < 0) {
        printf("n/a\n");
        return 0;
    }

    printf("%lld\n", fibonacci(n));
    return 0;
}

long long fibonacci(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}
