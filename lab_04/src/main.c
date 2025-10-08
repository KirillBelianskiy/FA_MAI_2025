#include <stdio.h>
#include <stdlib.h>
#include "../include/status_codes.h"
#include "../include/methods.h"
#include "../include/functions.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <epsilon>\n", argv[0]);
        return INVALID_ARGS;
    }

    char* endptr;
    double epsilon = strtod(argv[1], &endptr);

    if (*endptr != '\0' || endptr == argv[1])
    {
        fprintf(stderr, "Error: Invalid epsilon value\n");
        return INVALID_ARGS;
    }

    if (epsilon <= 0.0 || epsilon >= 1.0)
    {
        return INVALID_EPSILON;
    }


    double result;

    printf("Computing constants with epsilon = %e\n\n", epsilon);

    // Вычисление e
    printf("=== Computing e ===\n");
    int status = calculate_e_series(epsilon, &result);
    if (status == OK)
    {
        printf("e (series):   %.15f\n", result);
    }
    else
    {
        printf("e (series):   ");
        print_status_message(status);
    }

    status = calculate_e_equation(epsilon, &result);
    if (status == OK)
    {
        printf("e (equation): %.15f\n", result);
    }
    else
    {
        printf("e (equation): ");
        print_status_message(status);
    }

    status = calculate_e_limit(epsilon, &result);
    if (status == OK)
    {
        printf("e (limit):    %.15f\n", result);
    }
    else
    {
        printf("e (limit):    ");
        print_status_message(status);
    }

    // Вычисление π
    printf("\n=== Computing π ===\n");
    status = calculate_pi_series(epsilon, &result);
    if (status == OK)
    {
        printf("π (series):   %.15f\n", result);
    }
    else
    {
        printf("π (series):   ");
        print_status_message(status);
    }

    status = calculate_pi_equation(epsilon, &result);
    if (status == OK)
    {
        printf("π (equation): %.15f\n", result);
    }
    else
    {
        printf("π (equation): ");
        print_status_message(status);
    }

    status = calculate_pi_limit(epsilon, &result);
    if (status == OK)
    {
        printf("π (limit):    %.15f\n", result);
    }
    else
    {
        printf("π (limit):    ");
        print_status_message(status);
    }

    // Вычисление ln(2)
    printf("\n=== Computing ln(2) ===\n");
    status = calculate_ln2_series(epsilon, &result);
    if (status == OK)
    {
        printf("ln(2) (series):   %.15f\n", result);
    }
    else
    {
        printf("ln(2) (series):   ");
        print_status_message(status);
    }

    status = calculate_ln2_equation(epsilon, &result);
    if (status == OK)
    {
        printf("ln(2) (equation): %.15f\n", result);
    }
    else
    {
        printf("ln(2) (equation): ");
        print_status_message(status);
    }

    status = calculate_ln2_limit(epsilon, &result);
    if (status == OK)
    {
        printf("ln(2) (limit):    %.15f\n", result);
    }
    else
    {
        printf("ln(2) (limit):    ");
        print_status_message(status);
    }

    // Вычисление √2
    printf("\n=== Computing √2 ===\n");
    status = calculate_sqrt2_series(epsilon, &result);
    if (status == OK)
    {
        printf("√2 (series):   %.15f\n", result);
    }
    else
    {
        printf("√2 (series):   ");
        print_status_message(status);
    }

    status = calculate_sqrt2_equation(epsilon, &result);
    if (status == OK)
    {
        printf("√2 (equation): %.15f\n", result);
    }
    else
    {
        printf("√2 (equation): ");
        print_status_message(status);
    }

    status = calculate_sqrt2_limit(epsilon, &result);
    if (status == OK)
    {
        printf("√2 (limit):    %.15f\n", result);
    }
    else
    {
        printf("√2 (limit):    ");
        print_status_message(status);
    }

    // Вычисление γ
    printf("\n=== Computing γ (Euler-Mascheroni constant) ===\n");
    status = calculate_gamma_series(epsilon, &result);
    if (status == OK)
    {
        printf("γ (series):   %.15f\n", result);
    }
    else
    {
        printf("γ (series):   ");
        print_status_message(status);
    }

    status = calculate_gamma_equation(epsilon, &result);
    if (status == OK)
    {
        printf("γ (equation): %.15f\n", result);
    }
    else
    {
        printf("γ (equation): ");
        print_status_message(status);
    }

    status = calculate_gamma_limit(epsilon, &result);
    if (status == OK)
    {
        printf("γ (limit):    %.15f\n", result);
    }
    else
    {
        printf("γ (limit):    ");
        print_status_message(status);
    }

    printf("\n");

    return OK;
}
