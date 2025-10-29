#include "../include/overfprintf.h"
#include "../include/new_flags.h"
#include "../include/oversprintf.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int overfprintf(FILE* stream, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    int written_count = 0;
    const char* p = format;

    char buffer[256];

    while (*p != '\0')
    {
        if (*p != '%')
        {
            fputc(*p, stream);
            written_count++;
            p++;
            continue;
        }

        p++;

        switch (*p)
        {
        case '%':
            fputc('%', stream);
            written_count++;
            break;

        case 'R':
            if (*(p + 1) == 'o')
            {
                int num = va_arg(args, int);
                if (to_rome(num, buffer) == 0)
                {
                    fputs(buffer, stream);
                    written_count += strlen(buffer);
                }
                p++;
            }
            break;

        case 'Z':
            if (*(p + 1) == 'r')
            {
                unsigned int num = va_arg(args, unsigned int);
                if (to_zeckendorf(num, buffer) == 0)
                {
                    fputs(buffer, stream);
                    written_count += strlen(buffer);
                }
                p++;
            }
            break;

        case 'C':
            {
                int val = va_arg(args, int);
                int base_to = va_arg(args, int);
                int is_upper = (*(p + 1) == 'V');

                if (base_to < 2 || base_to > 36) base_to = 10;

                char int_str[33];
                sprintf(int_str, "%d", val);

                if (from_K_to_N(int_str, 10, base_to, is_upper, buffer) == 0)
                {
                    fputs(buffer, stream);
                    written_count += strlen(buffer);
                }

                p++;
            }
            break;

        case 't':
        case 'T':
            {
                int is_upper = (*p == 'T');
                if (*(p + 1) == 'o')
                {
                    char* val_str = va_arg(args, char*);
                    int base_from = va_arg(args, int);

                    if (base_from < 2 || base_from > 36) base_from = 10;

                    if (from_K_to_N(val_str, base_from, 10, is_upper, buffer) == 0)
                    {
                        fputs(buffer, stream);
                        written_count += strlen(buffer);
                    }

                    p++;
                }
            }
            break;

        case 'm':
            switch (*(p + 1))
            {
            case 'i':
                {
                    int val = va_arg(args, int);
                    int len = memory_dump_helper(buffer, &val, sizeof(val));
                    fputs(buffer, stream);
                    written_count += len;
                }
                p++;
                break;
            case 'u':
                {
                    unsigned int val = va_arg(args, unsigned int);
                    int len = memory_dump_helper(buffer, &val, sizeof(val));
                    fputs(buffer, stream);
                    written_count += len;
                }
                p++;
                break;
            case 'd':
                {
                    double val = va_arg(args, double);
                    int len = memory_dump_helper(buffer, &val, sizeof(val));
                    fputs(buffer, stream);
                    written_count += len;
                }
                p++;
                break;
            case 'f':
                {
                    double val_d = va_arg(args, double);
                    float val_f = (float)val_d;
                    int len = memory_dump_helper(buffer, &val_f, sizeof(val_f));
                    fputs(buffer, stream);
                    written_count += len;
                }
                p++;
                break;
            }
            break;

        case 'c':
            {
                char c = (char)va_arg(args, int);
                fputc(c, stream);
                written_count++;
                break;
            }

        case 's':
            {
                char* s = va_arg(args, char*);
                if (s == NULL)
                {
                    s = "(null)";
                }
                fputs(s, stream);
                written_count += strlen(s);
                break;
            }

        case 'd':
        case 'i':
            {
                int val = va_arg(args, int);
                oversprintf(buffer, "%d", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }

        case 'u':
            {
                unsigned int val = va_arg(args, unsigned int);
                oversprintf(buffer, "%u", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }

        case 'f':
            {
                double val = va_arg(args, double);
                oversprintf(buffer, "%f", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }

        case 'x':
            {
                unsigned int val = va_arg(args, unsigned int);
                oversprintf(buffer, "%x", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }

        case 'X':
            {
                unsigned int val = va_arg(args, unsigned int);
                oversprintf(buffer, "%X", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }

        case 'p':
            {
                void* val = va_arg(args, void*);
                oversprintf(buffer, "%p", val);
                fputs(buffer, stream);
                written_count += strlen(buffer);
                break;
            }


        default:
            fputc('%', stream);
            fputc(*p, stream);
            written_count += 2;
            break;
        }

        p++;
    }

    va_end(args);
    return written_count;
}
