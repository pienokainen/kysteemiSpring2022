#include <stdio.h>

void sum_and_print(int num1, int num2) {
    int sum = num1 + num2;
    float multiplication = sum * num1 * num2;
    printf("Sum of the numbers is: %d\n", sum);
    printf("Multiplication of sum, number1 and number2 is: %f\n", multiplication);
}