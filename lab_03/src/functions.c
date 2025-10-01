#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "../include/status_codes.h"

int eq(const double eps, const double a, const double b)
{
    if (eps < 0) return NEGATIVE_NUMBER;

    if (fabs(a - b) < eps) return 1;
    return 0;
}

int less(const double eps, const double a, const double b)
{
    if (eps < 0) return NEGATIVE_NUMBER;
    if (b - a > eps) return 1;
    return 0;
}

int less_or_eq(const double eps, const double a, const double b)
{
    if (eps < 0) return NEGATIVE_NUMBER;
    if (less(eps, a, b) || eq(eps, a, b)) return 1;
    return 0;
}


int greater(const double eps, const double a, const double b)
{
    if (eps < 0) return NEGATIVE_NUMBER;
    if (a - b > eps) return 1;
    return 0;
}

int greater_or_eq(const double eps, const double a, const double b)
{
    if (eps < 0) return NEGATIVE_NUMBER;
    if (greater(eps, a, b) || eq(eps, a, b)) return 1;
    return 0;
}

int swap(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
    return OK;
}

int parse_input(const int argc, const char** argv, double* nums, char* f)
{
    if (argc < 2 || (argv[1][0] != '-' && argv[1][0] != '/'))
    {
        return INCORRECT_INPUT;
    }
    char flag = argv[1][1];
    *f = flag;

    if (flag == 'q' || flag == 't') {
        if (argc != 6) return INCORRECT_COUNT_INPUT;
    } else if (flag == 'm') {
        if (argc != 4) return INCORRECT_COUNT_INPUT;
    } else {
        return INCORRECT_INPUT;
    }

    for (int i = 2; i < argc; i++)
    {
        char *endptr;
        double value = strtod(argv[i], &endptr);

        if (*endptr != '\0' || argv[i] == endptr)
        {
            return 1;
        }

        if (value == HUGE_VAL || value == -HUGE_VAL)
        {
            return 1;
        }

        if (eq(10e-10, value, 0.0) || less(10e-10, value, 0.0))
        {
            return 1;
        }

        nums[i-2] = value;
    }
    return OK;
}


int find_solutions(const double eps, const double a, const double b, const double c, double* sol, int* count)
{
    if (eps < 0) return NEGATIVE_NUMBER;

    if (eq(eps, a, 0))
    {
        if (eq(eps, b, 0))
        {
            if (eq(eps, c, 0))
            {
                return INFINITY_SOL;
            }
            return ZERO_SOL;
        }
        sol[0] = - c / b;
        *count = 1;
        return OK;
    }

    double D = b * b - 4 * a * c;
    if (eq(eps, D, 0))
    {
        sol[0] = - b / (2 * a);
        *count = 1;
        return OK;
    }
    if (less(eps, D, 0))
    {
        return ZERO_SOL;
    }

    double sqrt_D = sqrt(D);

    sol[0] = (-b + sqrt_D) / (2 * a);
    sol[1] = (-b - sqrt_D) / (2 * a);
    *count = 2;

    return OK;
}

int possible_solutions(const double eps, const double a, const double b, const double c)
{
    if (eps < 0) return NEGATIVE_NUMBER;

    double coefficients[3] = {a, b, c};
    double solutions[2];
    int count;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (i == j)
            {
                continue;
            }
            for (int k = 0; k < 3; ++k)
            {
                if (k == i || k == j)
                {
                    continue;
                }


                int root_count = find_solutions(eps, coefficients[i], coefficients[j], coefficients[k], solutions, &count);
                if (root_count == ZERO_SOL)
                {
                    printf("Zero solution for this coefficients: %.02lf, %.02lf, %.02lf\n",
                        coefficients[i], coefficients[j], coefficients[k]);
                }
                else if (root_count == INFINITY_SOL)
                {
                    printf("Infinity solutions for this coefficients: %.02lf, %.02lf, %.02lf\n",
                        coefficients[i], coefficients[j], coefficients[k]);
                }
                else if (count == 1)
                {
                    printf("%.02lf is solution for this coefficients: %.02lf, %.02lf, %.02lf\n",
                        solutions[0], coefficients[i], coefficients[j], coefficients[k]);
                }
                else if (count == 2)
                {
                    printf("%.02lf and %.02lf are solutions for this coefficients: %.02lf, %.02lf, %.02lf\n",
                        solutions[0], solutions[1], coefficients[i], coefficients[j], coefficients[k]);
                }
            }
        }
    }
    return OK;
}


int is_multiple(const int a, const int b)
{
    if (a == 0 || b == 0) return INCORRECT_ARGUMENTS;
    if (a % b == 0)
    {
        return MULTIPLE;
    }
    return NOT_MULTIPLE;
}

int is_triangular(const double eps, const double a, const double b, const double c)
{
    if (eps < 0) return NEGATIVE_NUMBER;
    if (less(eps, a, 0) || less(eps, b, 0) || less(eps, c, 0))
    {
        return NEGATIVE_NUMBER;
    }
    if (less_or_eq(eps, a + b, c) && less_or_eq(eps, a + c, b) && less_or_eq(eps, b + c, a))
    {
        return INCORRECT_INPUT;
    }

    double hyp_sq, leg1_sq, leg2_sq;

    double a_sq = a * a;
    double b_sq = b * b;
    double c_sq = c * c;

    if (greater_or_eq(eps, a, b) && greater_or_eq(eps, a, c))
    {
        hyp_sq = a_sq;
        leg1_sq = b_sq;
        leg2_sq = c_sq;
    }
    else if (greater_or_eq(eps, b, a) && greater_or_eq(eps, b, c))
    {
        hyp_sq = b_sq;
        leg1_sq = a_sq;
        leg2_sq = c_sq;
    }
    else
    {
        hyp_sq = c_sq;
        leg1_sq = a_sq;
        leg2_sq = b_sq;
    }

    if (eq(eps, hyp_sq, leg1_sq + leg2_sq))
    {
        printf("The given side lengths can form a valid triangle according to the triangle inequality theorem.\n");
        return OK;
    }
    printf("The given side lengths cannot form a valid triangle, as they violate the triangle inequality theorem.\n");
    return OK;
}

void print_errors(const int err)
{
    switch (err)
    {
    case OK: return;
    case NEGATIVE_NUMBER: printf("The provided epsilon value is negative, which is invalid for comparison purposes.\n"); break;
    case INCORRECT_INPUT: printf("The input provided is incorrect or malformed, please check the format and try again.\n"); break;
    case INCORRECT_COUNT_INPUT: printf("The number of arguments passed is incorrect; please verify the required count and provide the appropriate inputs.\n"); break;
    case ZERO_SOL: printf("The equation has zero real solutions, meaning no roots satisfy the conditions.\n"); break;
    case INFINITY_SOL: printf("The equation has infinitely many solutions, as it simplifies to an identity like 0 = 0.\n"); break;
    case INCORRECT_ARGUMENTS: printf("The arguments provided are incorrect or invalid for the operation being performed.\n"); break;
    case MULTIPLE: printf("The first number is a multiple of the second number.\n"); break;
    case NOT_MULTIPLE: printf("The first number is not a multiple of the second number.\n"); break;
    default: printf("An unknown error code was encountered; please check the input or contact support for assistance.\n"); break;
    }
}