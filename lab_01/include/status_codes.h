#pragma once

enum status_codes
{
    OK,
    NEGATIVE_NUMBER,
    INCORRECT_NUMBER,
    INCORRECT_ARGUMENTS,
    INCORRECT_COUNT_INPUT,
};

typedef enum kOpts {
    OPT_H,
    OPT_P,
    OPT_S,
    OPT_E,
    OPT_A,
    OPT_F
} kOpts;