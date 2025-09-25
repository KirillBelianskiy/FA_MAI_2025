#pragma once

enum status_codes
{
    OK,
    NEGATIVE_NUMBER,
    LARGE_NUMBER,
    INCORRECT_ARGUMENT,
    INCORRECT_NUMBER,
    UNKNOW_FLAG,
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