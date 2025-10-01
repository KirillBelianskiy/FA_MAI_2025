#pragma once

double trapezoid_method(const double b1, const double b2, const int n, double (*f)(double));

int runge_rule(const double eps, double int_2n, double int_n);

double calc_integral(const double eps, const double a, const double b, double (*f)(double));
