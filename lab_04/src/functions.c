#include <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

double my_fabs(double x)
{
    return x < 0 ? -x : x;
}

void print_status_message(int status)
{
    switch (status)
    {
    case OK:
        break;
    case INVALID_ARGS:
        fprintf(stderr, "Error: Invalid arguments\n");
        break;
    case INVALID_EPSILON:
        fprintf(stderr, "Error: Epsilon must be in range (0, 1)\n");
        break;
    case MEMORY_ERROR:
        fprintf(stderr, "Error: Memory allocation failed\n");
        break;
    case CONVERGENCE_ERROR:
        fprintf(stderr, "Error: Series/method did not converge\n");
        break;
    }
}
