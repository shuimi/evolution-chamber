//
// Created by Vladimir on 20.05.2021.
//

#include "Maths.h"

int Maths::fibonacci(int number) {
    if (number == 0) return 0;
    if (number == 1) return 1;
    return fibonacci(number - 1) + fibonacci(number - 2);
}

