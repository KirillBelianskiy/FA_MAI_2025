#include <stdio.h>
#include <math.h>
#include <float.h>

#include "../include/methods.h"
#include "../include/functions.h"
#include "../include/status_codes.h"

int calculate_e_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    const int max_iterations = 10000;

    while (n < max_iterations)
    {
        term /= n;
        if (my_fabs(term) < epsilon)
        {
            break;
        }
        sum += term;
        n++;
    }

    if (n >= max_iterations)
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
    const int max_iterations = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double ln_x = log(x);
        x = x - (ln_x - 1.0) * x;
        iteration++;

        if (iteration >= max_iterations)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > DBL_EPSILON);

    *result = x;
    return OK;
}

int calculate_e_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double prev_value = 0.0;
    double current_value;
    long long n = 1;
    const long long max_n = 100000000LL;
    int stable_count = 0;

    while (n < max_n)
    {
        current_value = pow(1.0 + 1.0 / n, (double)n);

        if (n > 1)
        {
            double diff = my_fabs(current_value - prev_value);
            if (diff < epsilon)
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

    *result = current_value;
    return OK;
}

int calculate_pi_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double sum = 0.0;
    double term;
    long long n = 1;
    const long long max_iterations = 100000000;

    do
    {
        term = ((n - 1) % 2 == 0 ? 1.0 : -1.0) / (2.0 * n - 1.0);
        sum += term;
        n++;

        if (n >= max_iterations)
        {
            break;
        }
    }
    while (my_fabs(term) >= epsilon / 4.0);

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
    const int max_iterations = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double cos_x = cos(x);
        double sin_x = sin(x);

        if (my_fabs(sin_x) < 1e-10)
        {
            break;
        }

        x = x - (cos_x + 1.0) / (-sin_x);
        iteration++;

        if (iteration >= max_iterations)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > DBL_EPSILON);

    *result = x;
    return OK;
}

int calculate_pi_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < DBL_EPSILON * 10.0 ? DBL_EPSILON * 10.0 : epsilon;
    double prev_value = 0.0;
    double current_value;
    int n = 1;
    const int max_n = 100;
    int stable_count = 0;

    while (n < max_n)
    {
        double product = 1.0;
        for (int k = 1; k <= n; k++)
        {
            double ratio = (2.0 * k * 2.0 * k) / ((2.0 * k - 1.0) * (2.0 * k + 1.0));
            product *= ratio;
        }
        current_value = 2.0 * product;

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
        n++;
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

    double effective_eps = epsilon < DBL_EPSILON * 10.0 ? DBL_EPSILON * 10.0 : epsilon;
    double sum = 0.0;
    double term;
    long long n = 1;
    const long long max_iterations = 1000000000LL;

    do
    {
        term = ((n - 1) % 2 == 0 ? 1.0 : -1.0) / (double)n;
        sum += term;
        n++;

        if (n >= max_iterations)
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
    const int max_iterations = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        double exp_x = exp(x);
        x = x - (exp_x - 2.0) / exp_x;
        iteration++;

        if (iteration >= max_iterations)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > DBL_EPSILON);

    *result = x;
    return OK;
}

int calculate_ln2_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < DBL_EPSILON * 10.0 ? DBL_EPSILON * 10.0 : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 10;
    const long long max_n = 100000000LL;
    int stable_count = 0;

    while (n < max_n)
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

    *result = current_value;
    return OK;
}

int calculate_sqrt2_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double product = 1.0;
    double prev_product;
    int k = 2;
    const int max_iterations = 100;

    do
    {
        prev_product = product;
        double exponent = pow(2.0, -k);
        double factor = pow(2.0, exponent);
        product *= factor;
        k++;

        if (k >= max_iterations)
        {
            break;
        }
    }
    while (my_fabs(product - prev_product) >= epsilon);

    *result = product;
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
    const int max_iterations = 1000;
    int iteration = 0;

    do
    {
        prev_x = x;
        x = (x + 2.0 / x) / 2.0;
        iteration++;

        if (iteration >= max_iterations)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (my_fabs(x - prev_x) >= epsilon && my_fabs(x - prev_x) > DBL_EPSILON);

    *result = x;
    return OK;
}

int calculate_sqrt2_limit(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < DBL_EPSILON ? DBL_EPSILON : epsilon;
    double x_n = -0.5;
    double x_next;
    const int max_iterations = 10000;
    int iteration = 0;

    do
    {
        x_next = x_n - (x_n * x_n) / 2.0 + 1.0;

        double diff = my_fabs(x_next - x_n);
        if (diff < effective_eps)
        {
            break;
        }

        x_n = x_next;
        iteration++;

        if (iteration >= max_iterations)
        {
            return CONVERGENCE_ERROR;
        }
    }
    while (1);

    *result = x_next;
    return OK;
}

int calculate_gamma_series(double epsilon, double* result)
{
    if (result == NULL)
    {
        return INVALID_ARGS;
    }

    double effective_eps = epsilon < DBL_EPSILON * 10.0 ? DBL_EPSILON * 10.0 : epsilon;
    double pi_squared_over_6 = (M_PI * M_PI) / 6.0;
    double sum = -pi_squared_over_6;
    double term;
    long long k = 2;

    do
    {
        term = 1.0 / (floor(sqrt((double)k)) * floor(sqrt((double)k))) - 1.0 / k;
        sum += term;
        k++;
    }
    while (my_fabs(term) >= effective_eps || k < 20000);

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

    double effective_eps = epsilon < DBL_EPSILON * 10.0 ? DBL_EPSILON * 10.0 : epsilon;
    double prev_value = 0.0;
    double current_value;
    long long n = 100;
    const long long max_n = 100000000LL;
    int stable_count = 0;

    while (n < max_n)
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

    *result = current_value;
    return OK;
}
