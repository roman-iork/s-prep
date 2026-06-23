#include <stdio.h>
#include <stdlib.h>

int inputN(int *n);
int inputArr(int *a, int n);
void sort(int *a, int n);
void output(int *a, int n);

int main() {
    int n;
    if (inputN(&n) != 1) {
        printf("n/a");
        return 0;
    }

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("n/a");
        return 0;
    }

    if (inputArr(arr, n) != 1) {
        printf("n/a");
        return 0;
    }

    sort(arr, n);
    output(arr, n);

    // free memory
    free(arr);
    // null pointer
    arr = NULL;
    return 0;
}

int inputN(int *n){
    int d = scanf("%d", n);
    char c = getchar();
    if (d != 1 || c != '\n') return 0;
    return 1;
}


int inputArr(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int read = scanf("%d", a + i);
        char c = getchar();
        if (read == 1) {
            if (c == ' ' || c == '\n') {}
            else
                return 0;
        } else
            return 0;
    }
    return 1;
}

void sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_i = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min_i]) min_i = j;
        }
        if (min_i != i) {
            int temp_m = a[min_i];
            a[min_i] = a[i];
            a[i] = temp_m;
        }
    }
}

void output(int *a, int n) {
    printf("%d", *a);
    for (int i = 1; i < n; i++) {
        printf(" %d", *(a + i));
    }
}
