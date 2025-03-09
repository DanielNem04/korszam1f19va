#include <iostream>
#include <cmath>

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


int main() {
	std::cout.precision(16);
	std::cout << integrate(10, -1.0, 3.0) << std::endl;
	return 0;
}