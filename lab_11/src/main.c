#include <stdio.h>

#include "../include /functions.h"
#include "../include /status_codes.h"

int main()
{
    int vc = is_infinite_fraction(10, 1, 1.0 / 3.0);

    print_errors(vc);
    return 0;
}
