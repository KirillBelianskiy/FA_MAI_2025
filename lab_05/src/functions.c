#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "../include/functions.h"
#include "../include/status_codes.h"

int delete_digits(FILE *inp, FILE *outp)
{
    int ch;
    while ((ch = fgetc(inp)) != EOF)
    {
        if (!isdigit(ch))
        {
            fputc(ch, outp);
        }
    }
    return OK;
}

int count_latin_letters(FILE *inp, FILE *outp)
{
    char str[1024];
    while (fgets(str, 1024, inp))
    {
        int count = 0;
        for (int i = 0; str[i] != '\n' && str[i] != '\0'; ++i)
        {
            if (isalpha(str[i]))
            {
               count++;
            }
        }
        fprintf(outp, "%d\n", count);
    }
    return OK;
}

int count_unusual_symb(FILE *inp, FILE *outp)
{
    char str[1024];
    while (fgets(str, 1024, inp))
    {
        int count = 0;
        for (int i = 0; str[i] != '\n' && str[i] != '\0'; ++i)
        {
            if (!(isalpha(str[i]) || isdigit(str[i]) || str[i] == ' '))
            {
                count++;
            }
        }
        fprintf(outp, "%d\n", count);
    }
    return OK;
}

int change_to_ascii(FILE *inp, FILE *outp)
{
    int ch;
    while ((ch = fgetc(inp)) != EOF)
    {
        if (!isdigit(ch))
        {
            fprintf(outp, "%02x ", ch);
        }
        else
        {
            fprintf(outp, "%c ", ch);
        }
    }
    return OK;
}

int GetOpts(int argc, const char **argv, kOpts *option, FILE **input, FILE **output)
{
    if (argc < 3 || argc > 4)
    {
        return INCORRECT_COUNT_INPUT;
    }

    if (argv[1][0] != '-' && argv[1][0] != '/')
    {
        return INCORRECT_INPUT;
    }

    *input = fopen(argv[2], "r");
    if (*input == NULL)
    {
        return ERROR_OPEN_FILE;
    }

    char output_filename[FILENAME_MAX];
    int use_n_flag = (argv[1][1] == 'n');

    if (use_n_flag && argc != 4)
    {
        fclose(*input);
        return INCORRECT_COUNT_INPUT;
    }
    if (!use_n_flag && argc != 3)
    {
        fclose(*input);
        return INCORRECT_COUNT_INPUT;
    }

    if (use_n_flag)
    {
        snprintf(output_filename, sizeof(output_filename), "%s", argv[3]);
    }
    else
    {
        snprintf(output_filename, sizeof(output_filename), "out_%s", argv[2]);
    }

    if (strcmp(argv[2], output_filename) == 0)
    {
        fclose(*input);
        return INCORRECT_INPUT;
    }

    *output = fopen(output_filename, "w");
    if (*output == NULL)
    {
        fclose(*input);
        return ERROR_OPEN_FILE;
    }

    char action_flag = use_n_flag ? argv[1][2] : argv[1][1];

    switch (action_flag)
    {
    case 'd': *option = OPT_D; break;
    case 'i': *option = OPT_I; break;
    case 's': *option = OPT_S; break;
    case 'a': *option = OPT_A; break;
    default:
        fclose(*input);
        fclose(*output);
        return UNKNOWN_FLAG;
    }
    return OK;
}

void print_errors(const int error_code)
{
    switch (error_code)
    {
    case OK: break;
    case ERROR_OPEN_FILE: printf("The file cannot be opened\n"); break;
    case ERROR_MEMORY_ALLOCATION: printf("Memory allocation failure\n"); break;
    case INCORRECT_COUNT_INPUT: printf("Incorrect number of arguments\n"); break;
    case INCORRECT_INPUT: printf("Incorrect input\n"); break;
    case UNKNOWN_FLAG: printf("A unknown flag\n"); break;
    default: printf("A unknown error\n"); break;
    }
}