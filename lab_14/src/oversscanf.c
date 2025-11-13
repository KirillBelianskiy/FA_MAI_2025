#include "../include/new_flags.h"
#include "../include/oversscanf.h"

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int oversscanf(const char* str, const char* format, ...)
{
    if (str == NULL || format == NULL)
    {
        return 0;
    }

    va_list args;
    va_start(args, format);

    int reading_count = 0;
    const char* p = format;
    bool parsing_active = true;

    while (*p != '\0' && parsing_active)
    {
        if (isspace(*p))
        {
            while (isspace(*str))
            {
                str++;
            }
            p++;
            continue;
        }

        if (*p == '%')
        {
            p++;

            if (*p != 'c')
            {
                while (isspace(*str))
                {
                    str++;
                }
            }

            switch (*p)
            {
            case '%':
                if (*str == '%')
                {
                    str++;
                }
                else
                {
                    parsing_active = false;
                }
                break;

            case 'R':
                if (*(p + 1) == 'o')
                {
                    p++;
                    int* arabic_num = va_arg(args, int*);
                    char rome_num[32]; // Буфер 32
                    int i = 0;

                    while (i < 31 && rome_arabic(*str) != -1)
                    {
                        rome_num[i++] = *str++;
                    }
                    rome_num[i] = '\0';

                    if (i == 0)
                    {
                        parsing_active = false;
                        break;
                    }

                    int res = from_rome(rome_num);

                    if (res == -1)
                    {
                        parsing_active = false;
                    }
                    else
                    {
                        *arabic_num = res;
                        reading_count++;
                    }
                }
                else
                {
                    parsing_active = false;
                }
                break;

            case 'Z':
                if (*(p + 1) == 'r')
                {
                    p++;
                    int* res_num = va_arg(args, int*);
                    char zeckendorf[65];
                    int i = 0;

                    while (i < 64 && (*str == '0' || *str == '1'))
                    {
                        zeckendorf[i++] = *str++;
                    }
                    zeckendorf[i] = 0;

                    if (i == 0)
                    {
                        parsing_active = false;
                        break;
                    }

                    int res = from_zeckendorf(zeckendorf);

                    if (res == -1)
                    {
                        parsing_active = false;
                    }
                    else
                    {
                        *res_num = res;
                        reading_count++;
                    }
                }
                else
                {
                    parsing_active = false;
                }
                break;

            case 'C':
                {
                    int is_upper = 0;
                    char next_char = *(p + 1);

                    if (next_char == 'v')
                    {
                        is_upper = 0;
                        p++;
                    }
                    else if (next_char == 'V')
                    {
                        is_upper = 1;
                        p++;
                    }
                    else
                    {
                        parsing_active = false;
                        break;
                    }

                    int* res_num = va_arg(args, int*);
                    int base = va_arg(args, int);

                    if (base < 2 || base > 36)
                    {
                        base = 10;
                    }

                    int sign = 1;
                    if (*str == '-')
                    {
                        sign = -1;
                        str++;
                    }
                    else if (*str == '+')
                    {
                        str++;
                    }

                    long long parsed_value = 0;
                    int digits_read = 0;

                    while (true)
                    {
                        int digit_val = parse_digit(*str, base, is_upper);

                        if (digit_val == -1)
                        {
                            break;
                        }

                        parsed_value = parsed_value * base + digit_val;
                        str++;
                        digits_read++;
                    }

                    if (digits_read > 0)
                    {
                        *res_num = (int)(parsed_value * sign);
                        reading_count++;
                    }
                    else
                    {
                        parsing_active = false;
                    }
                }
                break;
            case 'd':
                {
                    int* res_num = va_arg(args, int*);
                    char* end_ptr;
                    long res = strtol(str, &end_ptr, 10);

                    if (str == end_ptr)
                    {
                        parsing_active = false;
                    }
                    else
                    {
                        *res_num = (int)res;
                        str = end_ptr;
                        reading_count++;
                    }
                }
                break;

            case 's':
                {
                    char* dest_str = va_arg(args, char*);
                    if (*str == '\0')
                    {
                        parsing_active = false;
                        break;
                    }

                    int i = 0;

                    while (*str != '\0' && !isspace(*str))
                    {
                        *dest_str = *str;
                        dest_str++;
                        str++;
                        i++;
                    }
                    *dest_str = '\0';

                    if (i > 0)
                    {
                        reading_count++;
                    }
                    else
                    {
                        parsing_active = false;
                    }
                }
                break;

            case 'c':
                {
                    char* dest_char = va_arg(args, char*);
                    if (*str == '\0')
                    {
                        parsing_active = false;
                    }
                    else
                    {
                        *dest_char = *str;
                        str++;
                        reading_count++;
                    }
                }
                break;

            default:
                parsing_active = false;
            }
            p++;
            continue;
        }

        if (*p == *str)
        {
            p++;
            str++;
        }
        else
        {
            parsing_active = false;
        }
    }

    va_end(args);
    return reading_count;
}
