#include "math_hw.h"

double my_exp(double x_e) {
    double z = x_e;
    return (1.0+0.5*z+0.1*z*z+(1.0/120.0)*z*z*z)/(1.0-0.5*z+0.1*z*z-(1.0/120.0)*z*z*z);
}

double my_cos(double x_c) {
    double w = x_c;
    return (1.0-w*w*(115.0/252.0)+w*w*w*w*(313.0/15120.0))/(1+w*w*(11.0/252.0)+w*w*w*w*(13.0/15120.0));
}