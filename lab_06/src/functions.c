#include <math.h>
#include <stdlib.h>

#include "../include/functions.h"

int eq(const double eps, const double a, const double b)
{
    if (eps < 0) return 0;

    if (fabs(a - b) < eps) return 1;
    return 0;
}

int less(const double eps, const double a, const double b)
{
    if (eps < 0) return 0;

    if (b - a > eps) return 1;
    return 0;
}

double func_a(double x)
{
    if (eq(10e-10, x, 0.0)) return 1.0;

    return log(1.0 + x) / x;
}

double func_b(double x)
{
    return exp(-x * x / 2.0);
}

double func_c(double x)
{
    if (eq(10e-10, x, 1)) return 0.99999999;

    return log(1.0 / (1.0 - x));
}

double func_d(double x)
{
    if (eq(10e-10, x, 0.0)) return 1.0;

    return pow(x, x);
}

int parse_input(const int argc, char** argv, double* eps)
{
    if (argc != 2)
    {
        return 1;
    }

    char *endptr;
    double eps_value = strtod(argv[1], &endptr);

    if (*endptr != '\0' || argv[1] == endptr)
    {
        return 1;
    }

    if (eps_value == HUGE_VAL || eps_value == -HUGE_VAL)
    {
        return 1;
    }

    if (eq(10e-10, eps_value, 0.0) || less(10e-10, eps_value, 0.0))
    {
        return 1;
    }

    *eps = eps_value;
    return 0;
}