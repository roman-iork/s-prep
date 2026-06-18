#include <stdio.h>
#include <math.h>

void encode(void);
void decode(void);
int is_hex_digit(int c);
int hex_to_val(int c);

int main(int argc, char **argv) {
    /* Проверяем аргументы без использования strcmp */
    if (argc != 2 || argv[1][0] == '\0' || argv[1][1] != '\0') {
        printf("n/a");
        return 0;
    }

    if (argv[1][0] == '0') {
        encode();
    } else if (argv[1][0] == '1') {
        decode();
    } else {
        printf("n/a");
    }

    return 0;
}

void encode(void) {
    int current;
    int next;
    int first = 1;
    int has_input = 0;

    current = getchar();
    if (current == '\n' || current == EOF) {
        printf("n/a");
        return;
    }

    while (current != '\n' && current != EOF) {
        next = getchar();

        /* Валидация структуры: за символом должен идти пробел или конец строки */
        if (next != ' ' && next != '\n' && next != EOF) {
            printf("n/a");
            return;
        }

        if (!first) {
            printf(" ");
        }
        printf("%02X", current);
        first = 0;
        has_input = 1;

        if (next == ' ') {
            current = getchar();
            /* Два пробела подряд или пробел перед концом строки — ошибка */
            if (current == ' ' || current == '\n' || current == EOF) {
                printf("n/a");
                return;
            }
        } else {
            current = next;
        }
    }

    if (!has_input) {
        printf("n/a");
    }
}

void decode(void) {
    int c1, c2, sep;
    int first = 1;
    int has_input = 0;

    while (1) {
        c1 = getchar();
        if (first && (c1 == '\n' || c1 == EOF)) {
            printf("n/a");
            return;
        }

        if (!is_hex_digit(c1)) {
            printf("n/a");
            return;
        }

        c2 = getchar();
        if (!is_hex_digit(c2)) {
            printf("n/a");
            return;
        }

        /* Вычисляем значение ASCII-символа из двух шестнадцатеричных цифр */
        int ascii_code = hex_to_val(c1) * 16 + hex_to_val(c2);
        
        /* Стандартный ASCII включает символы от 0 до 127 */
        if (ascii_code > 127) {
            printf("n/a");
            return;
        }

        if (!first) {
            printf(" ");
        }
        printf("%c", (char)ascii_code);
        first = 0;
        has_input = 1;

        sep = getchar();
        if (sep == '\n' || sep == EOF) {
            break;
        }
        
        /* Разделителем между парами hex-символов должен быть строго один пробел */
        if (sep != ' ') {
            printf("n/a");
            return;
        }
    }

    if (!has_input) {
        printf("n/a");
    }
}

int is_hex_digit(int c) {
    return ((c >= '0' && c <= '9') || 
            (c >= 'A' && c <= 'F') || 
            (c >= 'a' && c <= 'f'));
}

int hex_to_val(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}
