#pragma once

enum status_codes
{
    OK,
    ERROR_OPEN_FILE,
    ERROR_MEMORY_ALLOCATION,
    INCORRECT_COUNT_INPUT,
    INCORRECT_INPUT,
    UNKNOWN_FLAG
};

typedef enum
{
    OPT_D,
    OPT_I,
    OPT_S,
    OPT_A
} kOpts;