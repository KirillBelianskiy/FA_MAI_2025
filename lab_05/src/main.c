#include <stdio.h>

#include "../include/status_codes.h"
#include "../include/functions.h"

int main(int argc, char **argv)
{
    kOpts opt;
    FILE *input = NULL;
    FILE *output = NULL;

    int rc = GetOpts(argc, argv, &opt, &input, &output);
    print_errors(rc);

    callback_t handlers[] = {
        delete_digits,
        count_latin_letters,
        count_unusual_symb,
        change_to_ascii
    };

    handlers[opt](input, output);

    if (input) fclose(input);
    if (output) fclose(output);
    return 0;
}