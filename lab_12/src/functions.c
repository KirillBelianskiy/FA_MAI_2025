#include <stdio.h>

#include "../include /functions.h"

void* memchr(const void* str, int c, size_t n)
{
    if (str == NULL)
    {
        return NULL;
    }

    const unsigned char* p = (const unsigned char*)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        if (p[i] == uc)
        {
            return (void*)(p + i);
        }
    }
    return NULL;
}

int memcmp(const void* str1, const void* str2, size_t n)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    const unsigned char* p1 = (const unsigned char*)str1;
    const unsigned char* p2 = (const unsigned char*)str2;

    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    char* d = (char*)dest;
    const char* s = (const char*)src;

    for (size_t i = 0; i < n; i++)
    {
        d[i] = s[i];
    }

    return dest;
}


void* memset(void* str, int c, size_t n)
{
    if (str == NULL)
    {
        return NULL;
    }

    unsigned char* p = (unsigned char*)str;
    unsigned char uc = (unsigned char)c;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = uc;
    }
    return str;
}

char* strncat(char* dest, const char* src, size_t n)
{
    if (dest == NULL || src == NULL)
    {
        return dest;
    }

    size_t dest_len = strlen(dest);
    size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';

    return dest;
}

char* strchr(const char* str, int c)
{
    if (str == NULL)
    {
        return NULL;
    }

    char* ptr = (char*)str;
    char ch = (char)c;

    while (*ptr != '\0')
    {
        if (*ptr == ch)
        {
            return ptr;
        }
        ptr++;
    }

    if (ch == '\0')
    {
        return ptr;
    }

    return NULL;
}

int strncmp(const char* str1, const char* str2, size_t n)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    for (size_t i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
        {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        if (str1[i] == '\0')
        {
            return 0;
        }
    }
    return 0;
}

char* strncpy(char* dest, const char* src, size_t n)
{
    if (dest == NULL || src == NULL)
    {
        return dest;
    }

    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    for (; i < n; i++)
    {
        dest[i] = '\0';
    }

    return dest;
}

size_t strcspn(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }

    size_t i;
    for (i = 0; str1[i] != '\0'; i++)
    {
        if (strchr(str2, str1[i]) != NULL)
        {
            return i;
        }
    }
    return i;
}

char* strerror(int errnum)
{
    static char *messages[] = {
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "I/O error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file number",
        "No child processes",
        "Try again",
        "Out of memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Device or resource busy",
        "File exists",
        "Cross-device link",
        "No such device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "File table overflow",
        "Too many open files",
        "Not a typewriter",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Math argument out of domain of func",
        "Math result not representable",
        "Resource deadlock would occur",
        "File name too long",
        "No record locks available",
        "Invalid system call number",
        "Directory not empty",
        "Too many symbolic links encountered",
        "Operation would block",
        "No message of desired type",
        "Identifier removed",
        "Channel number out of range",
        "Level 2 not synchronized",
        "Level 3 halted",
        "Level 3 reset",
        "Link number out of range",
        "Protocol driver not attached",
        "No CSI structure available",
        "Level 2 halted",
        "Invalid exchange",
        "Invalid request descriptor",
        "Exchange full",
        "No anode",
        "Invalid request code",
        "Invalid slot",
        "",
        "Resource deadlock would occur",
        "Bad font file format",
        "Device not a stream",
        "No data available",
        "Timer expired",
        "Out of streams resources",
        "Machine is not on the network",
        "Package not installed",
        "Object is remote",
        "Link has been severed",
        "Advertise error",
        "Srmount error",
        "Communication error on send",
        "Protocol error",
        "Multihop attempted",
        "RFS specific error",
        "Not a data message",
        "Value too large for defined data type",
        "Name not unique on network",
        "File descriptor in bad state",
        "Remote address changed",
        "Can not access a needed shared library",
        "Accessing a corrupted shared library",
        ".lib section in a.out corrupted",
        "Attempting to link in too many shared libraries",
        "Cannot exec a shared library directly",
        "Illegal byte sequence",
        "Interrupted system call should be restarted",
        "Streams pipe error",
        "Too many users",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported on transport endpoint",
        "Protocol family not supported",
        "Address family not supported by protocol",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection because of reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Transport endpoint is already connected"
    };
    return messages[errnum];
}

size_t strlen(const char* str)
{
    if (str == NULL)
    {
        return 0;
    }

    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

char* strpbrk(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
    {
        return NULL;
    }

    char* ptr = (char*)str1;
    while (*ptr != '\0')
    {
        if (strchr(str2, *ptr) != NULL)
        {
            return ptr;
        }
        ptr++;
    }
    return NULL;
}

char* strrchr(const char* str, int c)
{
    if (str == NULL)
    {
        return NULL;
    }

    char* last_occurrence = NULL;
    char ch = (char)c;

    while (*str != '\0')
    {
        if (*str == ch)
        {
            last_occurrence = (char*)str;
        }
        str++;
    }

    if (ch == '\0')
    {
        return (char*)str;
    }

    return last_occurrence;
}

char* strstr(const char* haystack, const char* needle)
{
    if (haystack == NULL || needle == NULL)
    {
        return NULL;
    }

    if (*needle == '\0')
    {
        return (char*)haystack;
    }

    size_t needle_len = strlen(needle);
    char* ptr = (char*)haystack;

    while (*ptr != '\0')
    {
        if (strncmp(ptr, needle, needle_len) == 0)
        {
            return ptr;
        }
        ptr++;
    }
    return NULL;
}

char* strtok(char* str, const char* delim)
{
    static char* next;
    if (str == NULL)
    {
        str = next;
    }
    if (str == NULL)
    {
        return NULL;
    }

    char* start = str;
    int is_delim;
    while (*start != '\0')
    {
        is_delim = 0;
        for (const char* d = delim; *d != '\0'; d++)
        {
            if (*start == *d)
            {
                is_delim = 1;
                break;
            }
        }
        if (!is_delim) break;
        start++;
    }

    if (*start == '\0')
    {
        next = NULL;
        return NULL;
    }

    char* end = start;
    while (*end != '\0')
    {
        is_delim = 0;
        for (const char* d = delim; *d != '\0'; d++)
        {
            if (*end == *d)
            {
                is_delim = 1;
                break;
            }
        }
        if (is_delim) break;
        end++;
    }

    if (*end != '\0')
    {
        *end = '\0';
        next = end + 1;
    }
    else
    {
        next = NULL;
    }

    return start;
}
