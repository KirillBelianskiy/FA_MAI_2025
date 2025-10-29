#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "../include/oversprintf.h"
#include "../include/new_flags.h"

void reverse_str(char* str, int len)
{
    int i = 0, j = len - 1;
    char temp;
    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int my_itoa(int val, char* buf)
{
    int i = 0;
    int is_negative = 0;
    unsigned int num;

    if (val == 0)
    {
        buf[i++] = '0';
        buf[i] = '\0';
        return i;
    }

    if (val < 0)
    {
        is_negative = 1;
        num = (unsigned int)(-val);
    }
    else
    {
        num = (unsigned int)val;
    }

    while (num != 0)
    {
        buf[i++] = (num % 10) + '0';
        num = num / 10;
    }

    if (is_negative)
    {
        buf[i++] = '-';
    }

    buf[i] = '\0';
    reverse_str(buf, i);
    return i;
}

int my_utoa(unsigned int num, char* buf)
{
    int i = 0;
    if (num == 0)
    {
        buf[i++] = '0';
        buf[i] = '\0';
        return i;
    }

    while (num != 0)
    {
        buf[i++] = (num % 10) + '0';
        num = num / 10;
    }

    buf[i] = '\0';
    reverse_str(buf, i);
    return i;
}


int my_uto_hex(unsigned long long num, char* buf, int is_upper)
{
    const char* digits = is_upper ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0;

    if (num == 0)
    {
        buf[i++] = '0';
        buf[i] = '\0';
        return i;
    }

    while (num != 0)
    {
        buf[i++] = digits[num % 16];
        num = num / 16;
    }

    buf[i] = '\0';
    reverse_str(buf, i);
    return i;
}

int my_ftoa(double val, char* buf, int precision)
{
    int i = 0;
    int is_negative = 0;

    if (val < 0)
    {
        is_negative = 1;
        val = -val;
    }

    unsigned long long ipart = (unsigned long long)val;
    double fpart = val - (double)ipart;

    if (ipart == 0)
    {
        buf[i++] = '0';
    }
    else
    {
        int ipart_len = 0;
        unsigned long long temp_ipart = ipart;
        while (temp_ipart != 0)
        {
            buf[i++] = (temp_ipart % 10) + '0';
            temp_ipart /= 10;
            ipart_len++;
        }
        reverse_str(buf, ipart_len);
    }

    if (is_negative)
    {
        for (int j = i; j > 0; j--) buf[j] = buf[j - 1];
        buf[0] = '-';
        i++;
    }

    if (precision > 0)
    {
        buf[i++] = '.';

        double multiplier = 1.0;
        for (int k = 0; k < precision; k++)
        {
            multiplier *= 10.0;
        }

        unsigned long long fpart_num = (unsigned long long)(fpart * multiplier + 0.5);

        char temp_fbuf[32];
        int f_i = 0;
        if (fpart_num == 0)
        {
            temp_fbuf[f_i++] = '0';
        }
        else
        {
            while (fpart_num != 0)
            {
                temp_fbuf[f_i++] = (fpart_num % 10) + '0';
                fpart_num /= 10;
            }
        }

        while (f_i < precision)
        {
            temp_fbuf[f_i++] = '0';
        }

        for (int k = f_i - 1; k >= 0; k--)
        {
            buf[i++] = temp_fbuf[k];
        }
    }

    buf[i] = '\0';
    return i;
}

int oversprintf(char* str, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    int written_count = 0;
    const char* p = format;
    char* s = str;

    char buffer[256];

    while (*p != '\0')
    {
        if (*p != '%')
        {
            *s++ = *p;
            written_count++;
            p++;
            continue;
        }

        p++;
        int len = 0;

        switch (*p)
        {
        case '%':
            *s++ = '%';
            written_count++;
            break;

        case 'R':
            if (*(p + 1) == 'o')
            {
                int num = va_arg(args, int);
                if (to_rome(num, buffer) == 0)
                {
                    len = strlen(buffer);
                    memcpy(s, buffer, len);
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
                    len = strlen(buffer);
                    memcpy(s, buffer, len);
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
                my_itoa(val, int_str);

                if (from_K_to_N(int_str, 10, base_to, is_upper, buffer) == 0)
                {
                    len = strlen(buffer);
                    memcpy(s, buffer, len);
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
                        len = strlen(buffer);
                        memcpy(s, buffer, len);
                    }
                    p++;
                }
            }
            break;

        case 'm':
            {
                switch (*(p + 1))
                {
                case 'i':
                    {
                        int val_i = va_arg(args, int);
                        len = memory_dump_helper(s, &val_i, sizeof(val_i));
                    }
                    p++;
                    break;
                case 'u':
                    {
                        unsigned int val_u = va_arg(args, unsigned int);
                        len = memory_dump_helper(s, &val_u, sizeof(val_u));
                    }
                    p++;
                    break;
                case 'd':
                    {
                        double val_d = va_arg(args, double);
                        len = memory_dump_helper(s, &val_d, sizeof(val_d));
                    }
                    p++;
                    break;
                case 'f':
                    {
                        double val_d = va_arg(args, double);
                        float val_f = (float)val_d;
                        len = memory_dump_helper(s, &val_f, sizeof(val_f));
                    }
                    p++;
                    break;
                }
            }
            break;
        case 'c':
            *s++ = (char)va_arg(args, int);
            written_count++;
            p++;
            continue;
        case 's':
            {
                char* str_arg = va_arg(args, char*);
                if (str_arg == NULL)
                {
                    str_arg = "(null)";
                }
                len = strlen(str_arg);
                memcpy(s, str_arg, len);
            }
            break;

        case 'd':
        case 'i':
            len = my_itoa(va_arg(args, int), s);
            break;

        case 'u':
            len = my_utoa(va_arg(args, unsigned int), s);
            break;

        case 'f':
            len = my_ftoa(va_arg(args, double), s, 6);
            break;

        case 'x':
            len = my_uto_hex(va_arg(args, unsigned int), s, 0);
            break;

        case 'X':
            len = my_uto_hex(va_arg(args, unsigned int), s, 1);
            break;

        case 'p':
            {
                uintptr_t ptr_val = (uintptr_t)va_arg(args, void*);
                *s++ = '0';
                *s++ = 'x';
                written_count += 2;
                len = my_uto_hex((unsigned long long)ptr_val, s, 0);
            }
            break;

        default:
            *s++ = '%';
            *s++ = *p;
            written_count += 2;
            p++;
            continue;
        }

        s += len;
        written_count += len;
        p++;
    }

    *s = '\0';
    va_end(args);
    return written_count;
}
