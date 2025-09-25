#include <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int main(int argc, char** argv) {
    kOpts opt;
    int number;

    if (GetOpts(argc, argv, &opt, &number)) {
        printf("Incorrect option or arguments");
        return 1;
    }

    callback_t handlers[] = {
        find_natural_numbers,
        is_prime,
        table_of_degrees,
        sum_to_num,
        sum_to_num,
        factorial
    };

    int rc = handlers[opt](number);
    print_errors(rc);

    return 0;
}