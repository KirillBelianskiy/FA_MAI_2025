#include <stdio.h>

#include "../include /functions.h"

void print_hex(const char* label, const void* data, size_t n)
{
    printf("%s", label);
    const unsigned char* p = (const unsigned char*)data;
    for (size_t i = 0; i < n; i++)
    {
        printf("%02X ", p[i]);
    }
    printf("\n");
}

int main()
{
    printf("=== Starting tests for 15 functions ===\n\n");

    // --- 1. memchr ---
    printf("--- Test memchr ---\n");
    const char* mem = "This is a test memory block";
    printf("Searching for 'b' in \"%s\" (n=30)\n", mem);
    char* found_mem = (char*)memchr(mem, 'b', 30);
    printf("Result: %s\n", found_mem ? found_mem : "NULL");
    printf("Searching for 'Z' in \"%s\" (n=30)\n", mem);
    found_mem = (char*)memchr(mem, 'Z', 30);
    printf("Result: %s\n", found_mem ? found_mem : "NULL");
    printf("Searching for 's' in \"%s\" (n=2)\n", mem); // Limit test
    found_mem = (char*)memchr(mem, 's', 2);
    printf("Result: %s\n", found_mem ? found_mem : "NULL");
    printf("\n");

    // --- 2. memcmp ---
    printf("--- Test memcmp ---\n");
    printf("Comparing \"abcde\" and \"abcde\" (n=5): %d (Expect: 0)\n", memcmp("abcde", "abcde", 5));
    printf("Comparing \"abcde\" and \"abXde\" (n=5): %d (Expect: < 0)\n", memcmp("abcde", "abXde", 5));
    printf("Comparing \"abXde\" and \"abcde\" (n=5): %d (Expect: > 0)\n", memcmp("abXde", "abcde", 5));
    printf("Comparing \"abcde\" and \"abXde\" (n=2): %d (Expect: 0)\n", memcmp("abcde", "abXde", 2));
    printf("\n");

    // --- 3. memcpy ---
    printf("--- Test memcpy ---\n");
    char cpy_dest[20];
    const char* cpy_src = "Copied!"; // 7_chars + \0 = 8
    memcpy(cpy_dest, cpy_src, 8);
    printf("Copied \"%s\" into dest. Result: %s\n", cpy_src, cpy_dest);
    printf("\n");

    // --- 4. memset ---
    printf("--- Test memset ---\n");
    char set_dest[15];
    printf("Filling 10 bytes with 'Z' char\n");
    memset(set_dest, 'Z', 10);
    set_dest[10] = '\0'; // Add \0 for printf
    printf("Result: \"%s\"\n", set_dest);
    printf("\n");

    // --- 5. strncat ---
    printf("--- Test strncat ---\n");
    char ncat_dest[50] = "Hello, ";
    const char* ncat_src = "world! Extra text.";
    printf("Before: \"%s\"\n", ncat_dest);
    strncat(ncat_dest, ncat_src, 5); // "world"
    printf("After (n=5):  \"%s\"\n", ncat_dest);
    strncat(ncat_dest, ncat_src, 50); // n > src length
    printf("After (n=50): \"%s\"\n", ncat_dest);
    printf("\n");

    // --- 6. strchr ---
    printf("--- Test strchr ---\n");
    const char* s_chr = "Find the first 'f' char";
    printf("Searching for 'f' in \"%s\"\n", s_chr);
    printf("Result: %s\n", strchr(s_chr, 'f'));
    printf("Searching for 'z' in \"%s\"\n", s_chr);
    printf("Result: %s\n", strchr(s_chr, 'z') ? "Found" : "NULL");
    printf("Searching for '\\0' in \"%s\"\n", s_chr);
    char* null_char = strchr(s_chr, '\0');
    printf("Result (pointer to \\0): %d\n", (null_char && *null_char == '\0'));
    printf("\n");

    // --- 7. strncmp ---
    printf("--- Test strncmp ---\n");
    printf("Comparing \"Test\" and \"Test\" (n=4): %d (Expect: 0)\n", strncmp("Test", "Test", 4));
    printf("Comparing \"TestA\" and \"TestB\" (n=5): %d (Expect: < 0)\n", strncmp("TestA", "TestB", 5));
    printf("Comparing \"TestA\" and \"TestB\" (n=4): %d (Expect: 0)\n", strncmp("TestA", "TestB", 4));
    printf("Comparing \"TestA\" and \"Test\" (n=5): %d (Expect: > 0)\n", strncmp("TestA", "Test", 5));
    printf("\n");

    // --- 8. strncpy ---
    printf("--- Test strncpy ---\n");
    char ncpy_dest[20];
    const char* ncpy_src = "Short";
    printf("Copying \"Short\" (n=15)...\n");
    strncpy(ncpy_dest, ncpy_src, 15);
    print_hex("Result (HEX, note the \\0 padding): ", ncpy_dest, 15);
    printf("String: \"%s\"\n", ncpy_dest);
    const char* ncpy_src2 = "A very long string";
    printf("Copying \"A very long...\" (n=10)...\n");
    strncpy(ncpy_dest, ncpy_src2, 10);
    ncpy_dest[10] = '\0'; // Your function doesn't add \0 if n < src_len
    printf("Result (truncated): \"%s\"\n", ncpy_dest);
    printf("\n");

    // --- 9. strcspn ---
    printf("--- Test strcspn ---\n");
    const char* cspn1 = "abc_def|ghi";
    const char* cspn2 = "_|";
    printf("String: \"%s\", Chars: \"%s\"\n", cspn1, cspn2);
    printf("Result (length of 'abc'): %zu (Expect: 3)\n", strcspn(cspn1, cspn2));
    printf("String: \"abcdef\", Chars: \"xyz\"\n");
    printf("Result (length of 'abcdef'): %zu (Expect: 6)\n", strcspn("abcdef", "xyz"));
    printf("\n");

    // --- 10. strerror ---
    printf("--- Test strerror (using your implementation) ---\n");
    printf("Error 0: %s\n", strerror(0));
    printf("Error 1: %s\n", strerror(1));
    printf("Error 10: %s\n", strerror(10));
    printf("Error 99: %s\n", strerror(99));
    printf("\n");

    // --- 11. strlen ---
    printf("--- Test strlen ---\n");
    printf("Length of \"Hello\": %zu (Expect: 5)\n", strlen("Hello"));
    printf("Length of \"\": %zu (Expect: 0)\n", strlen(""));
    printf("Length of NULL: %zu (Expect: 0)\n", strlen(NULL));
    printf("\n");

    // --- 12. strpbrk ---
    printf("--- Test strpbrk ---\n");
    const char* pbrk1 = "Find_any|char";
    const char* pbrk2 = "|_";
    printf("String: \"%s\", Chars: \"%s\"\n", pbrk1, pbrk2);
    printf("Result: %s\n", strpbrk(pbrk1, pbrk2));
    printf("String: \"abcdef\", Chars: \"xyz\"\n");
    printf("Result: %s\n", strpbrk("abcdef", "xyz") ? "Found" : "NULL");
    printf("\n");

    // --- 13. strrchr ---
    printf("--- Test strrchr ---\n");
    const char* r_chr = "Find the last 's' char";
    printf("Searching for 's' in \"%s\"\n", r_chr);
    printf("Result: %s\n", strrchr(r_chr, 's'));
    printf("Searching for 'z' in \"%s\"\n", r_chr);
    printf("Result: %s\n", strrchr(r_chr, 'z') ? "Found" : "NULL");
    printf("\n");

    // --- 14. strstr ---
    printf("--- Test strstr ---\n");
    const char* haystack = "In a haystack, find a needle";
    const char* needle1 = "needle";
    const char* needle2 = "pin";
    printf("Haystack: \"%s\", Needle: \"%s\"\n", haystack, needle1);
    printf("Result: %s\n", strstr(haystack, needle1));
    printf("Haystack: \"%s\", Needle: \"%s\"\n", haystack, needle2);
    printf("Result: %s\n", strstr(haystack, needle2) ? "Found" : "NULL");
    printf("Searching for empty string: %s\n", strstr(haystack, ""));
    printf("\n");

    // --- 15. strtok ---
    printf("--- Test strtok ---\n");
    // Important: strtok modifies the string, so it cannot be const
    char tok_str[] = "one,two.three;four-five";
    const char* delim = ",.;-";
    printf("String: \"%s\", Delims: \"%s\"\n", tok_str, delim);
    char* token = strtok(tok_str, delim);
    while (token != NULL)
    {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    printf("\n");

    printf("=== Testing complete ===\n");
    return 0;
}