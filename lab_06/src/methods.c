#include "../include/methods.h"

#include <math.h>

double trapezoid_method(const double b1, const double b2, const int n, double (*f)(double))
{
    double h = (b2 - b1) / n;
    double sum = (f(b1) + f(b2)) / 2.0;
    for (int i = 1; i < n; ++i)
    {
        double x_i = b1 + i * h;
        sum += f(x_i);
    }

    return sum * h;
}

int runge_rule(const double eps, double int_2n, double int_n)
{
    if (fabs(int_2n - int_n) / 3.0 >= eps) return 1;

    return 0;
}

double calc_integral(const double eps, const double a, const double b, double (*f)(double))
{
    int n = 4;
    double int_n = trapezoid_method(a, b, n, f);

    n *= 2;
    double int_2n = trapezoid_method(a, b, n, f);

    while (runge_rule(eps, int_2n, int_n))
    {
        int_n = int_2n;
        n *= 2;
        int_2n = trapezoid_method(a, b, n, f);
    }
    return int_2n;
}