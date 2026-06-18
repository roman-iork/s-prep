#include <stdio.h>

// this function returns lpn
long long Lpn(long long num) {
    long long lpn = -1; // starting value
    long long factor = 2;  // first check if it's divided by 2

    // main loop that checks all - division by 2 by odd and discovers final lpn
    while (num > 1) {
        
        // first check if number can be divided by 2
        // next loops factor will be increased on 1
        long long remainder = num; // at first reminder equals num itself
        while (remainder >= factor) {
            // constantly renew reminder decreasing it on factor
            remainder -= factor;
        }

        // if reminder is 0 then factor is divider
        if (remainder == 0) {
            lpn = factor; // assigne it to lpd

            // try to divide num by factor til it is possible
            while (1) {
                // every time check new reminder if it still cna be divided
                long long temp_rem = num;
                while (temp_rem >= factor) {
                    temp_rem -= factor;
                }
                
                // if reminder is not 0 then no more division possible
                // leave decrision loop
                if (temp_rem != 0) {
                    break;
                }

                // here happens division lile with / operator
                long long quotient = 0; // this is result of division by factor
                long long temp_num = num; // copy num to change it's value safely
                while (temp_num >= factor) {
                    temp_num -= factor;
                    quotient++; // count how many times factor can be substracted
                }
                num = quotient; // now num becomes result of division
            }
        }
        factor++; // go to next factor
    }

    return lpn;
}

int main() {
    long long input_number;

    //printf("Введите положительное целое число: ");
    if (scanf("%lld", &input_number) != 1 || input_number <= 1) {
        printf("Ошибка: введите число больше 1.\n");
        return 1;
    }

    // Вызов функции подсчета
    long long result = Lpn(input_number);

    printf("Наибольший простой делитель: %lld\n", result);

    return 0;
}
