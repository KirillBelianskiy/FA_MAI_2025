#include <stdio.h>
#include <stdlib.h>
#include "../include/functons.h"
#include "../include/status_codes.h"

// сделать через указатель на функции (для проверки вводимых данных)

int main(int args, char** argv)
{

// TODO: переписать в функции проверки через указатель на функцию
    if (args != 3)
    {
        printf("Incorrect number of arguments");
        return 0;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/')
    {
        printf("Incorrect command");
        return 0;
    }
    char flag = argv[1][1];
    int num = atoi(argv[2]);

    int rc;

    switch (flag)
    {
    case 'h': rc = find_natural_numbers(num); break;
    case 'p': rc = is_prime(num); break;
    case 's': rc = table_of_degrees(num); break;
    case 'e': rc = sum_to_num(num); break;
    case 'a': rc = sum_to_num(num); break;
    case 'f': rc = factorial(num); break;
    default:
        printf("Incorrect command");
        return 0;
    }

    switch (rc)
    {
    case OK:
        break;
    case NEGATIVE_NUMBER:
        printf("Negative number");
        break;
    case LARGE_NUMBER:
        printf("Large number");
        break;
    case INCORRECT_NUMBER:
        printf("Incorrect number");
        break;
    default:
        printf("Unknown status");
        break;
    }

    return 0;
}