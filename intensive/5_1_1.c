//with speed increasing
#include <stdio.h>

int main() {
    int width = 80;
    int height = 25;

    int paddle1_y = 12;
    int paddle2_y = 12;

    int ball_x = 40;
    int ball_y = 12;
    int ball_dx = 1;
    int ball_dy = 1;

    int speed = 3; // Мяч летит по 2 символа за ход

    int score1 = 0;
    int score2 = 0;
    int game_over = 0;

    printf("=== ДОБРО ПОЖАЛОВАТЬ В PONG ===\n");
    printf("Игрок 1: A/Z | Игрок 2: K/M | Пропуск хода: Пробел\n");
    printf("После ввода клавиши ОБЯЗАТЕЛЬНО нажимайте Enter.\n");
    printf("Нажмите Enter, чтобы начать игру...");
    getchar(); 

    while (!game_over) {
        // Отрисовка поля
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (y == 0 || y == height - 1) {
                    printf("-");
                }
                else if (x == 2 && (y == paddle1_y - 1 || y == paddle1_y || y == paddle1_y + 1)) {
                    printf("|");
                }
                else if (x == width - 3 && (y == paddle2_y - 1 || y == paddle2_y || y == paddle2_y + 1)) {
                    printf("|");
                }
                else if (x == ball_x && y == ball_y) {
                    printf("*");
                }
                else if (y == 2 && x == (width / 2) - 3) {
                    printf("%02d", score1);
                    x++;
                }
                else if (y == 2 && x == (width / 2) + 2) {
                    printf("%02d", score2);
                    x++;
                }
                else if (x == width / 2) {
                    printf("|");
                }
                else if (x == 0 || x == width - 1) {
                    printf("|");
                }
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        printf("Ваш ход (A/Z, K/M или Пробел + Enter): ");
        
        char input_char;
        int valid_input = 0;

        while (!valid_input) {
            // Читаем символ через getchar, чтобы поймать пробел
            input_char = getchar();

            // Если считался символ перевода строки '\n' от прошлого ввода, пропускаем его
            if (input_char == '\n') {
                continue;
            }

            if (input_char == 'a' || input_char == 'A') {
                if (paddle1_y > 2) paddle1_y--;
                valid_input = 1;
            } else if (input_char == 'z' || input_char == 'Z') {
                if (paddle1_y < height - 3) paddle1_y++;
                valid_input = 1;
            } else if (input_char == 'k' || input_char == 'K') {
                if (paddle2_y > 2) paddle2_y--;
                valid_input = 1;
            } else if (input_char == 'm' || input_char == 'M') {
                if (paddle2_y < height - 3) paddle2_y++;
                valid_input = 1;
            } else if (input_char == ' ') {
                // Игрок нажал пробел. Ракетки не двигаются, флаг становится валидным
                valid_input = 1; 
            } else {
                printf("Неверный ввод! Нажмите A/Z, K/M или Пробел, затем Enter: ");
                // Очищаем буфер от остатков ввода (например, от нажатого Enter)
                while (getchar() != '\n'); 
            }
        }

        // Очистка входного потока от нажатого Enter, чтобы он не мешал на следующем ходу
        if (input_char != ' ') {
            while (getchar() != '\n');
        }

        // Движение мяча (физика)
        for (int step = 0; step < speed; step++) {
            ball_x += ball_dx;
            ball_y += ball_dy;

            if (ball_y <= 1 || ball_y >= height - 2) {
                ball_dy = -ball_dy;
            }

            if (ball_x == 3) {
                if (ball_y >= paddle1_y - 1 && ball_y <= paddle1_y + 1) {
                    ball_dx = -ball_dx;
                }
            }

            if (ball_x == width - 4) {
                if (ball_y >= paddle2_y - 1 && ball_y <= paddle2_y + 1) {
                    ball_dx = -ball_dx;
                }
            }

            if (ball_x <= 0) {
                score2++;
                ball_x = width / 2;
                ball_y = height / 2;
                ball_dx = 1;
                break;
            }
            if (ball_x >= width - 1) {
                score1++;
                ball_x = width / 2;
                ball_y = height / 2;
                ball_dx = -1;
                break;
            }
        }

        // Проверка победы
        if (score1 == 21) {
            printf("\n===================================\n");
            printf("ПОЗДРАВЛЯЕМ! ИГРОК 1 ПОБЕДИЛ (21 очко)!\n");
            printf("===================================\n");
            game_over = 1;
        } else if (score2 == 21) {
            printf("\n===================================\n");
            printf("ПОЗДРАВЛЯЕМ! ИГРОК 2 ПОБЕДИЛ (21 очко)!\n");
            printf("===================================\n");
            game_over = 1;
        }
    }

    return 0;
}
