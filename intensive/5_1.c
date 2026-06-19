#include <stdio.h>

int main() {
    // Размеры поля
    int width = 80;
    int height = 25;

    // Координаты ракеток (центр по вертикали)
    int paddle1_y = 12;
    int paddle2_y = 12;

    // Координаты и скорость мяча
    int ball_x = 40;
    int ball_y = 12;
    int ball_dx = 1;  // Изменение по X (1 - вправо, -1 - влево)
    int ball_dy = 1;  // Изменение по Y (1 - вниз, -1 - вверх)

    // Счет игроков
    int score1 = 0;
    int score2 = 0;

    int game_over = 0;

    printf("=== ДОБРО ПОЖАЛОВАТЬ В PONG ===\n");
    printf("Игрок 1: A/Z | Игрок 2: K/M | Пропуск: Пробел\n");
    printf("После каждого ввода нажимайте Enter.\n");
    printf("Нажмите Enter для начала матча...");
    getchar();

    while (!game_over) {
        // Отрисовка игрового поля
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                
                // 1. Верхняя и нижняя границы поля
                if (y == 0 || y == height - 1) {
                    printf("-");
                }
                // 2. Левая ракетка (X = 2)
                else if (x == 2 && (y == paddle1_y - 1 || y == paddle1_y || y == paddle1_y + 1)) {
                    printf("|");
                }
                // 3. Правая ракетка (X = 77)
                else if (x == width - 3 && (y == paddle2_y - 1 || y == paddle2_y || y == paddle2_y + 1)) {
                    printf("|");
                }
                // 4. Мяч
                else if (x == ball_x && y == ball_y) {
                    printf("*");
                }
                // 5. Вывод счета над центральной линией (на строке y = 2)
                else if (y == 2 && x == (width / 2) - 3) {
                    printf("%02d", score1); // Две цифры для счета игрока 1
                    x++; // Пропускаем один символ, так как вывели 2 цифры вместо одной
                }
                else if (y == 2 && x == (width / 2) + 2) {
                    printf("%02d", score2); // Две цифры для счета игрока 2
                    x++;
                }
                // 6. Вертикальная разделяющая линия по центру (X = 40)
                else if (x == width / 2) {
                    printf("|");
                }
                // 7. Боковые стены (визуальные границы экрана)
                else if (x == 0 || x == width - 1) {
                    printf("|");
                }
                // 8. Пустое пространство
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // Запрос ввода у игрока
        printf("Ваш ход (A/Z, K/M или Пробел + Enter): ");
        char input_char;
        int valid_input = 0;

        while (!valid_input) {
            scanf(" %c", &input_char);

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
                valid_input = 1; // Просто пропускаем ход, мяч продолжит лететь
            } else {
                printf("Неверный ввод! Используйте A/Z, K/M или Пробел: ");
            }
        }

        // Физика: Движение мяча (теперь строго на +1 или -1 шаг)
        ball_x += ball_dx;
        ball_y += ball_dy;

        // Отскок от верхней и нижней стен
        if (ball_y <= 1 || ball_y >= height - 2) {
            ball_dy = -ball_dy;
        }

        // Проверка столкновения с левой ракеткой (X = 2, мяч находится на X = 3)
        if (ball_x == 3) {
            if (ball_y >= paddle1_y - 1 && ball_y <= paddle1_y + 1) {
                ball_dx = -ball_dx; // Отскок вправо
            }
        }

        // Проверка столкновения с правой ракеткой (X = 77, мяч находится на X = 76)
        if (ball_x == width - 4) {
            if (ball_y >= paddle2_y - 1 && ball_y <= paddle2_y + 1) {
                ball_dx = -ball_dx; // Отскок влево
            }
        }

        // Гол правому игроку (мяч улетел за левую границу)
        if (ball_x <= 0) {
            score2++;
            ball_x = width / 2;
            ball_y = height / 2;
            ball_dx = 1; // Мяч летит к Игроку 2
        }

        // Гол левому игроку (мяч улетел за правую границу)
        if (ball_x >= width - 1) {
            score1++;
            ball_x = width / 2;
            ball_y = height / 2;
            ball_dx = -1; // Мяч летит к Игроку 1
        }

        // Проверка условий победы до 21 очка
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
