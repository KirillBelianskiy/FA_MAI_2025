#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "../include /functions.h"
#include "../include /status_codes.h"

int gcd(int a, int b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0)
    {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

double my_abs(double x)
{
    if (x < 0.0)
    {
        return -x;
    }
    return x;
}

void double_to_fraction(double x, int* numerator, int* denominator)
{
    const int max_iterations = 20;
    const int max_denominator = 1000000;
    const double eps = 1e-9;

    if (x < eps)
    {
        *numerator = 0;
        *denominator = 1;
        return;
    }

    int h1 = 1, h2 = 0;
    int k1 = 0, k2 = 1;
    double b = x;

    for (int i = 0; i < max_iterations; i++)
    {
        int a = (int)floor(b);
        int h = a * h1 + h2;
        int k = a * k1 + k2;

        if (k > max_denominator)
        {
            break;
        }

        if (my_abs((double)h / k - x) < eps)
        {
            *numerator = h;
            *denominator = k;
            return;
        }

        h2 = h1;
        h1 = h;
        k2 = k1;
        k1 = k;

        b = b - a;
        if (b < eps)
        {
            break;
        }
        b = 1.0 / b;
    }

    *numerator = h1;
    *denominator = k1;
}

int get_prime_factors(int base, int* factors)
{
    int count = 0;

    if (base % 2 == 0)
    {
        factors[count] = 2;
        count++;
        while (base % 2 == 0)
        {
            base /= 2;
        }
    }

    for (int i = 3; i * i <= base; i += 2)
    {
        if (base % i == 0)
        {
            factors[count] = i;
            count++;
            while (base % i == 0)
            {
                base /= i;
            }
        }
    }

    if (base > 1)
    {
        factors[count] = base;
        count++;
    }
    return count;
}

int is_infinite_fraction(int base, int count, ...)
{
    va_list args;
    va_start(args, count);

    if (base < 2)
    {
        va_end(args);
        return INCORRECT_BASE;
    }

    for (int i = 0; i < count; i++)
    {
        double x = va_arg(args, double);

        if (x <= 0.0)
        {
            va_end(args);
            return NEGATIVE_NUMBER;
        }
        if (x >= 1.0)
        {
            va_end(args);
            return INCORRECT_NUMBER;
        }

        int p, q;
        double_to_fraction(x, &p, &q);

        int g = gcd(p, q);
        p /= g;
        q /= g;

        int factors[32];
        int count_divisors = get_prime_factors(base, factors);

        int temp_q = q;
        for (int j = 0; j < count_divisors; j++)
        {
            while (temp_q % factors[j] == 0)
            {
                temp_q /= factors[j];
            }
        }

        if (temp_q == 1)
        {
            printf("%.10f (= %d/%d) in base %d is finite\n", x, p, q, base);
        }
        else
        {
            printf("%.10f (= %d/%d) in base %d is infinite\n", x, p, q, base);
        }
    }

    va_end(args);
    return OK;
}

void print_errors(int status_code)
{
    switch (status_code)
    {
    case OK:
        break;
    case INCORRECT_BASE:
        printf("Error: The base of the number system is incorrect (must be >= 2).\n");
        break;
    case LARGE_NUMBER:
        printf("Error: The number of decimal digits is too large for integer representation (overflow).\n");
        break;
    case NEGATIVE_NUMBER:
        printf("Error: Negative number or zero found (only numbers in (0; 1) are allowed).\n");
        break;
    case INCORRECT_NUMBER:
        printf("Error: Fraction is outside the allowed range (0; 1).\n");
        break;
    case INCORRECT_CALCULATION:
        printf("Error: The calculation is incorrect.\n");
        break;
    default:
        printf("Unknown error code: %d\n", status_code);
        break;
    }
}
