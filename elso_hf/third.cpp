#include <iostream>
#include "math_hw.h"

// Function
double func(double x_f) {
    return my_exp(-x_f * x_f) * my_cos(x_f);
}

// Simpson's rule
double integrate(int n, double x0, double x1) {
    if (n % 2 != 0) {  // Simpson's rule requires an even number of intervals
        ++n;
    }

    double dx = (x1 - x0) / n;
    double int_value = func(x0) + func(x1);

    for (int i = 1; i < n; i += 2) {
        int_value += 4 * func(x0 + i * dx);
    }

    for (int i = 2; i < n - 1; i += 2) {
        int_value += 2 * func(x0 + i * dx);
    }

    int_value *= dx / 3.0;
    return int_value;
}

int main() {
    std::cout.precision(16);
    std::cout << integrate(1000, -1.0, 3.0) << std::endl;
    return 0;
}
