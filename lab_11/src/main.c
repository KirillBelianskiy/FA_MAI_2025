#include <stdio.h>

#include "../include /functions.h"
#include "../include /status_codes.h"

int main()
{
    int vc = is_infinite_fraction(2, 1, 2.0 / 5.0);

    print_errors(vc);
    return 0;
}
