// methods.c
#include <stdio.h>
#include <math.h>

#include "../include/methods.h"
#include "../include/functions.h"
#include "../include/status_codes.h"

#define MACHINE_EPSILON 1e-15
#define MIN_EFFECTIVE_EPSILON 1e-14

int calculate_e_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    const int MAX_ITERATIONS = 10000;

    while (n < MAX_ITERATIONS)
    {
        term /= n;
        if (my_fabs(term) < epsilon)
        {
            break;
        }
        sum += term;
        n++;
    }

    if (n >= MAX_ITERATIONS)
    {
        return CONVERGENCE_ERROR;
    }

    *result = sum;
    return OK;
}

int calculate_e_equation(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double x = 2.5;
    double prev_x;
    const int MAX_ITERATIONS = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double ln_x = log(x);
        x = x - (ln_x - 1.0) * x;
        iteration++;

        if (iteration >= MAX_ITERATIONS)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > MACHINE_EPSILON);

    *result = x;
    return OK;
}

int calculate_e_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 1;
    const long long MAX_N = 100000000LL;
    int stable_count = 0;

    while (n < MAX_N)
    {
        current_value = pow(1.0 + 1.0 / n, (double)n);

        if (n > 1)
        {
            double diff = my_fabs(current_value - prev_value);
            if (diff < effective_eps)
            {
                stable_count++;
                if (stable_count >= 3)
                {
                    break;
                }
            }
            else
            {
                stable_count = 0;
            }
        }

        prev_value = current_value;
        if (n < 1000)
        {
            n *= 2;
        }
        else
        {
            n = (long long)(n * 1.5);
        }
    }

    if (stable_count < 3 && n >= MAX_N)
    {
        *result = current_value;
        return OK;
    }

    *result = current_value;
    return OK;
}

int calculate_pi_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double sum = 0.0;
    double term;
    long long n = 0;
    const long long MAX_ITERATIONS = 1000000000LL;

    do
    {
        term = (n % 2 == 0 ? 1.0 : -1.0) / (2.0 * n + 1.0);
        sum += term;
        n++;

        if (n >= MAX_ITERATIONS)
        {
            break;
        }
    }
    while (my_fabs(term) >= effective_eps / 4.0);

    *result = 4.0 * sum;
    return OK;
}

int calculate_pi_equation(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double x = 3.0;
    double prev_x;
    const int MAX_ITERATIONS = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double sin_x = sin(x);
        double cos_x = cos(x);

        if (my_fabs(cos_x) < 1e-10)
        {
            break;
        }

        x = x - sin_x / cos_x;
        iteration++;

        if (iteration >= MAX_ITERATIONS)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > MACHINE_EPSILON);

    *result = x;
    return OK;
}

int calculate_pi_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 10;
    const long long MAX_N = 100000000LL;
    int stable_count = 0;

    while (n < MAX_N)
    {
        current_value = 6.0 * n * sin(M_PI / (6.0 * n));

        if (n > 10)
        {
            double diff = my_fabs(current_value - prev_value);
            if (diff < effective_eps)
            {
                stable_count++;
                if (stable_count >= 3)
                {
                    break;
                }
            }
            else
            {
                stable_count = 0;
            }
        }

        prev_value = current_value;
        if (n < 1000)
        {
            n *= 2;
        }
        else
        {
            n = (long long)(n * 1.5);
        }
    }

    if (stable_count < 3 && n >= MAX_N)
    {
        *result = current_value;
        return OK;
    }

    *result = current_value;
    return OK;
}

int calculate_ln2_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double sum = 0.0;
    double term;
    long long n = 1;
    const long long MAX_ITERATIONS = 1000000000LL;

    do
    {
        term = (n % 2 == 1 ? 1.0 : -1.0) / (double)n;
        sum += term;
        n++;

        if (n >= MAX_ITERATIONS)
        {
            break;
        }
    }
    while (my_fabs(term) >= effective_eps);

    *result = sum;
    return OK;
}

int calculate_ln2_equation(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double x = 0.5;
    double prev_x;
    const int MAX_ITERATIONS = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double exp_x = exp(x);
        x = x - (exp_x - 2.0) / exp_x;
        iteration++;

        if (iteration >= MAX_ITERATIONS)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > MACHINE_EPSILON);

    *result = x;
    return OK;
}

int calculate_ln2_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 10;
    const long long MAX_N = 100000000LL;
    int stable_count = 0;

    while (n < MAX_N)
    {
        current_value = n * (pow(2.0, 1.0 / n) - 1.0);

        if (n > 10)
        {
            double diff = my_fabs(current_value - prev_value);
            if (diff < effective_eps)
            {
                stable_count++;
                if (stable_count >= 3)
                {
                    break;
                }
            }
            else
            {
                stable_count = 0;
            }
        }

        prev_value = current_value;
        if (n < 1000)
        {
            n *= 2;
        }
        else
        {
            n = (long long)(n * 1.5);
        }
    }

    if (stable_count < 3 && n >= MAX_N)
    {
        *result = current_value;
        return OK;
    }

    *result = current_value;
    return OK;
}

int calculate_sqrt2_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double sum = 1.0;
    double term = 1.0;
    double x = 0.5;
    int n = 1;
    const int MAX_ITERATIONS = 10000;

    for (int i = 1; i < MAX_ITERATIONS; i++)
    {
        term *= -(2 * i - 3) * x / (2 * i);
        if (my_fabs(term) < epsilon / 2.0)
        {
            break;
        }
        sum += term;
        n = i;
    }

    if (n >= MAX_ITERATIONS - 1)
    {
        return CONVERGENCE_ERROR;
    }

    *result = 2.0 * sum;
    return OK;
}

int calculate_sqrt2_equation(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double x = 1.5;
    double prev_x;
    const int MAX_ITERATIONS = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        x = (x + 2.0 / x) / 2.0;
        iteration++;

        if (iteration >= MAX_ITERATIONS)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > MACHINE_EPSILON);

    *result = x;
    return OK;
}

int calculate_sqrt2_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MACHINE_EPSILON ? MACHINE_EPSILON : epsilon;
    double a_n = 1.0;
    double a_next;
    const int MAX_ITERATIONS = 10000;
    int iteration = 0;

    do
    {
        a_next = (a_n + 2.0 / a_n) / 2.0;

        double diff = my_fabs(a_next - a_n);
        if (diff < effective_eps)
        {
            break;
        }

        a_n = a_next;
        iteration++;

        if (iteration >= MAX_ITERATIONS)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (1);

    *result = a_next;
    return OK;
}

int calculate_gamma_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double sum = 0.0;
    double term;
    long long k = 1;
    const long long MAX_ITERATIONS = 100000000LL;

    do
    {
        term = 1.0 / k - log(1.0 + 1.0 / k);
        sum += term;
        k++;

        if (k >= MAX_ITERATIONS)
        {
            break;
        }
    }
    while (my_fabs(term) >= effective_eps || k < 100);

    *result = sum;
    return OK;
}

int calculate_gamma_equation(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    (void)epsilon;

    long long n = 10000000LL;
    double sum = 0.0;

    for (long long k = 1; k <= n; k++)
    {
        sum += 1.0 / k;
    }

    *result = sum - log((double)n);
    return OK;
}

int calculate_gamma_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < MIN_EFFECTIVE_EPSILON ? MIN_EFFECTIVE_EPSILON : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 100;
    const long long MAX_N = 100000000LL;
    int stable_count = 0;

    while (n < MAX_N)
    {
        double sum = 0.0;
        for (long long k = 1; k <= n; k++)
        {
            sum += 1.0 / k;
        }
        current_value = sum - log((double)n);

        if (n > 100)
        {
            double diff = my_fabs(current_value - prev_value);
            if (diff < effective_eps)
            {
                stable_count++;
                if (stable_count >= 3)
                {
                    break;
                }
            }
            else
            {
                stable_count = 0;
            }
        }

        prev_value = current_value;
        if (n < 1000)
        {
            n *= 2;
        }
        else
        {
            n = (long long)(n * 1.5);
        }
    }

    if (stable_count < 3 && n >= MAX_N)
    {
        *result = current_value;
        return OK;
    }

    *result = current_value;
    return OK;
}
