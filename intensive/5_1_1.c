//with speed increasing
#include <stdio.h>
#include <unistd.h> // temp, to be dell later
#include <stdlib.h> // Необходима для функции atoi


int main(int arg, char *argv[]) {
    if (arg != 2) return 0;
    int width = 80;
    int height = 25;

    int paddle1_y = 12;
    int paddle2_y = 12;

    int ball_x = 40;
    int ball_y = 12;
    int ball_dx = 1;
    int ball_dy = 1;

    //int speed = 3; // set speed of the ball - steps per iteration?
    int speed = atoi(argv[1]);

    int score1 = 0;
    int score2 = 0;
    int game_over = 0;

    printf("=== Welcome PONG game! ===\n");
    printf("Player 1: A/Z | Player 2: K/M | Skip: Space\n");
    printf("ALWAYS press Enter to confirm input.\n");
    printf("Press Enter to start");
    getchar(); // this call waits for player to press Enter

    while (!game_over) {
        // first clear screen and move cursor up left corner
        printf("\033[2J\033[1;1H");

        // draw field
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (y == 0 || y == height - 1) {
                    printf("-"); // here we draw upper and lower borders
                }
                else if (x == 2 && (y == paddle1_y - 1 || y == paddle1_y || y == paddle1_y + 1)) {
                    printf("|"); // here we draw left paddle
                }
                else if (x == width - 3 && (y == paddle2_y - 1 || y == paddle2_y || y == paddle2_y + 1)) {
                    printf("|"); // here we draw right paddle
                }
                else if (x == ball_x && y == ball_y) {
                    printf("*"); // here we draw ball
                }
                else if (y == 2 && x == (width / 2) - 3) {
                    printf("%02d", score1);  //field width 2 digits and pad with leading zeros
                    x++; // shift x forward since score takes width 2
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
                    printf(" "); // fill empty field with spaces
                }
            }
            printf("\n");

            // it is temp to see that picture is written line by line (shell be del later with #include <unistd.h>)
            //usleep(80000);
        }

        printf("Press A/Z, K/M or Space + Enter: ");


        // here happens input reading and calculation
        char input_char; // main container for the read character
        int valid_input = 0; // at first any reading consider not valid

        // run this cycle until valid char was entered
        while (!valid_input) {
            // read input as char
            input_char = getchar();

            // if Enter was pressed several times consider it to be one press logically and keep reading
            if (input_char == '\n') { // uncomment continue to move only one setp at a time
            //    continue;
            }

            // moving of paddles or skipping
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
            } else if (input_char == ' ' || '\n') {
                // Space was pressed which is valid button, change value to 1(true)
                valid_input = 1;
            } else {
                printf("Invalid input! Press A/Z, K/M or Space + Enter: ");
                // if more then one valid or invalid char was entered read them all till Enter is pressed
                while (getchar() != '\n');
            }
        }

        // you are here
        // Очистка входного потока от нажатого Enter, чтобы он не мешал на следующем ходу
        //if (input_char != ' ') {
           // while (getchar() != '\n');
        //}

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
        
        // redraw scores
        //drawScore(score1, score2, width);
    }

    return 0;
}
