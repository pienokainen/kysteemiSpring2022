#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("No extra parameters given, program needs 2 numbers");
    }
    if (argc == 2) {
        printf("Program needs two parameters to sum them");
    }
    if (argc==3) {
        int num1 = atoi(argv[1]);
        int num2 = atoi(argv[2]);
        sum_and_print(num1, num2);
    }
}