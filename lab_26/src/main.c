#include <stdio.h>
#include <string.h>
#include "../include/check_brackets.h"

void run_test(const char* test_name, const char* str, int expected, int* passed_count, int* total_count) {
    int result = check_brackets(str);
    int success = (result == expected);

    printf("Test %d: %s\n", *total_count + 1, test_name);
    printf("  Input:    \"%s\"\n", str);
    printf("  Expected: %s\n", expected ? "NO (invalid)" : "YES (valid)");
    printf("  Got:      %s\n", result ? "NO (invalid)" : "YES (valid)");
    printf("  Status:   %s\n\n", success ? "PASSED" : "FAILED");

    (*total_count)++;
    if (success) (*passed_count)++;
}

int main() {
    int passed = 0;
    int total = 0;

    printf("=== BRACKET VALIDATION TESTS ===\n\n");

    // 1. Пустые строки и NULL
    run_test("Empty string", "", 0, &passed, &total);
    run_test("NULL pointer", NULL, 1, &passed, &total);

    // 2. Простые валидные случаи
    run_test("Simple parentheses", "()", 0, &passed, &total);
    run_test("Simple curly braces", "{}", 0, &passed, &total);
    run_test("Simple square brackets", "[]", 0, &passed, &total);
    run_test("Simple angle brackets", "<>", 0, &passed, &total);

    // 3. Вложенные валидные случаи
    run_test("Nested brackets 1", "({[]})", 0, &passed, &total);
    run_test("Nested brackets 2", "[{()}]", 0, &passed, &total);
    run_test("Nested brackets 3", "<([{}])>", 0, &passed, &total);
    run_test("Mixed valid brackets", "()[]{}<>", 0, &passed, &total);
    run_test("Complex nested", "({<[]>})", 0, &passed, &total);

    // 4. Последовательные валидные случаи
    run_test("Sequential brackets", "()[]{}<>", 0, &passed, &total);
    run_test("Multiple groups", "(){[]}<()>", 0, &passed, &total);

    // 5. Строки с другими символами
    run_test("With text 1", "abc(def)ghi", 0, &passed, &total);
    run_test("With text 3", "array[i] = value;", 0, &passed, &total);
    run_test("With numbers", "1 + (2 * [3 + {4 - 5}])", 0, &passed, &total);

    // 6. НЕВАЛИДНЫЕ случаи - несоответствие типов
    run_test("Mismatch 1", "(]", 1, &passed, &total);
    run_test("Mismatch 2", "[}", 1, &passed, &total);
    run_test("Mismatch 3", "<)", 1, &passed, &total);
    run_test("Mismatch 4", "{>", 1, &passed, &total);
    run_test("Mismatch 5", "([)]", 1, &passed, &total);
    run_test("Mismatch 6", "{(})", 1, &passed, &total);
    run_test("Mismatch 7", "<{[}]>", 1, &passed, &total);  // Ваш оригинальный тест

    // 7. НЕВАЛИДНЫЕ случаи - незакрытые скобки
    run_test("Unclosed 1", "(", 1, &passed, &total);
    run_test("Unclosed 2", "{[(", 1, &passed, &total);
    run_test("Unclosed 3", "()[]{", 1, &passed, &total);
    run_test("Unclosed 4", "({[]}", 1, &passed, &total);

    // 8. НЕВАЛИДНЫЕ случаи - лишние закрывающие скобки
    run_test("Extra closing 1", "())", 1, &passed, &total);
    run_test("Extra closing 2", "[]]", 1, &passed, &total);
    run_test("Extra closing 3", "{}>", 1, &passed, &total);
    run_test("Extra closing 4", "()]", 1, &passed, &total);

    // 9. НЕВАЛИДНЫЕ случаи - неправильный порядок
    run_test("Wrong order 1", ")(", 1, &passed, &total);
    run_test("Wrong order 2", "][", 1, &passed, &total);
    run_test("Wrong order 3", "}{", 1, &passed, &total);
    run_test("Wrong order 4", "><", 1, &passed, &total);

    // 10. Сложные невалидные случаи
    run_test("Complex invalid 1", "({[}])", 1, &passed, &total);
    run_test("Complex invalid 2", "([{)]}", 1, &passed, &total);
    run_test("Complex invalid 3", "<(>{)}", 1, &passed, &total);
    run_test("Complex invalid 4", "({<)>}", 1, &passed, &total);

    // 11. Длинные строки (проверка работы стека)
    run_test("Long valid", "((((((((()))))))))", 0, &passed, &total);
    run_test("Long invalid", "((((((((())))))))))", 1, &passed, &total);

    // 12. Специальные символы
    run_test("Special chars", "(!@#$%^&*()_+{})", 0, &passed, &total);

    printf("=== TEST SUMMARY ===\n");
    printf("Passed: %d/%d\n", passed, total);
    printf("Success rate: %.1f%%\n", (float)passed / total * 100);

    return (passed == total) ? 0 : 1;
}