#include "../include/new_flags.h"
#include "../include/overfscanf.h"

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int overfscanf(FILE* stream, const char* format, ...)
{
    if (stream == NULL || format == NULL)
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
            int c;
            while ((c = fgetc(stream)) != EOF && isspace(c))
            {
            }
            if (c != EOF)
            {
                ungetc(c, stream);
            }
            p++;
            continue;
        }

        if (*p == '%')
        {
            p++;

            if (*p != 'c')
            {
                int c;
                while ((c = fgetc(stream)) != EOF && isspace(c))
                {
                }
                if (c != EOF)
                {
                    ungetc(c, stream);
                }
            }

            switch (*p)
            {
            case '%':
                {
                    int c = fgetc(stream);
                    if (c == '%')
                    {
                    }
                    else
                    {
                        if (c != EOF)
                        {
                            ungetc(c, stream);
                        }
                        parsing_active = false;
                    }
                }
                break;

            case 'R':
                if (*(p + 1) == 'o')
                {
                    p++;
                    int* arabic_num = va_arg(args, int*);
                    char rome_num[32];
                    int i = 0;

                    int c;
                    while (i < 31 && (c = fgetc(stream)) != EOF)
                    {
                        if (rome_arabic(c) != -1)
                        {
                            rome_num[i++] = c;
                        }
                        else
                        {
                            ungetc(c, stream);
                            break;
                        }
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

                    int c;
                    while (i < 64 && (c = fgetc(stream)) != EOF)
                    {
                        if (c == '0' || c == '1')
                        {
                            zeckendorf[i++] = c;
                        }
                        else
                        {
                            ungetc(c, stream);
                            break;
                        }
                    }
                    zeckendorf[i] = '\0';

                    if (i == 0)
                    {
                        parsing_active = false;
                        break;
                    }

                    unsigned res = from_zeckendorf(zeckendorf);

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
                    int c = fgetc(stream);

                    if (c == '-')
                    {
                        sign = -1;
                    }
                    else if (c == '+')
                    {
                    }
                    else if (c != EOF)
                    {
                        ungetc(c, stream);
                    }

                    long long parsed_value = 0;
                    int digits_read = 0;

                    while ((c = fgetc(stream)) != EOF)
                    {
                        int digit_val = parse_digit(c, base, is_upper);

                        if (digit_val == -1)
                        {
                            ungetc(c, stream);
                            break;
                        }

                        parsed_value = parsed_value * base + digit_val;
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
                    long parsed_value = 0;
                    int sign = 1;
                    int digits_read = 0;

                    int c = fgetc(stream);

                    if (c == '-')
                    {
                        sign = -1;
                    }
                    else if (c == '+')
                    {
                    }
                    else if (c != EOF)
                    {
                        ungetc(c, stream);
                    }

                    while ((c = fgetc(stream)) != EOF && isdigit(c))
                    {
                        parsed_value = parsed_value * 10 + (c - '0');
                        digits_read++;
                    }

                    if (c != EOF)
                    {
                        ungetc(c, stream);
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

            case 's':
                {
                    char* dest_str = va_arg(args, char*);
                    int i = 0;
                    int c;

                    while ((c = fgetc(stream)) != EOF && !isspace(c))
                    {
                        dest_str[i++] = c;
                    }

                    if (c != EOF && isspace(c))
                    {
                        ungetc(c, stream);
                    }

                    dest_str[i] = '\0';

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
                    int c = fgetc(stream);

                    if (c != EOF)
                    {
                        *dest_char = c;
                        reading_count++;
                    }
                    else
                    {
                        parsing_active = false;
                    }
                }
                break;

            default:
                parsing_active = false;
            }
            p++;
            continue;
        }

        int c = fgetc(stream);
        if (c == *p)
        {
            p++;
        }
        else
        {
            if (c != EOF)
            {
                ungetc(c, stream);
            }
            parsing_active = false;
        }
    }

    va_end(args);
    return reading_count;
}