#include <iostream>
#include <cmath>

const double correct_int_value_for_p16=1.346387956803450; // Wolframalpha-rol

// Function
double func(double x_f) {
	double func_value = exp(-x_f*x_f)*cos(x_f);
	return func_value;
}

// Simpson's rule
double integrate(int n, double x0, double x1) {
	double int_value = 0.0;
	double dx = (x1-x0)/n;
	double xi = x0;

	for (int i=0; i<n-1; ++i) {
		double xi_1 = xi + 0.5 *dx;
		double xi_2 = xi_1 + 0.5 *dx;
		int_value += (dx/6) * (func(xi)+4*func(xi_1)+func(xi_2));
		xi += dx;
	}
	return int_value;
}

void precision_checker(int n, int s, double x0_input, double x1_input, double d_p) {
    double x=n;
    while (x<s+1) {
        double integral_value = integrate(n, x0_input, x1_input);
        double diff_percent = abs(integral_value-correct_int_value_for_p16)/correct_int_value_for_p16;
        if (diff_percent < d_p) {
            std::cout << "n=" << x << " estén OK, kisebb mint " << d_p << " eltérés! (" <<diff_percent << ")"  << std::endl;
        }
        else {
            std::cout << "n=" << x << " estén NEM elég pontos, " << diff_percent << " a relatív eltérés!" << std::endl;
        }
        x *=10;
            
    }
}



int main() {
	std::cout.precision(16);
    precision_checker(10, 10000, -1, 3, 0.001);
    return 0;
}