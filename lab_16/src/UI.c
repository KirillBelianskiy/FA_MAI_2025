#include "../include/UI.h"
#include <stdio.h>

void print_status_error(StatusCode status)
{
    switch (status)
    {
    case OK:
        printf("Operation completed successfully.\n");
        break;
    case ERROR_INVALID_ARGUMENT:
        printf("Error: Invalid argument provided.\n");
        break;
    case ERROR_MEMORY_ALLOCATION:
        printf("Error: Memory allocation failed.\n");
        break;
    case ERROR_FILE_OPEN:
        printf("Error: Could not open file.\n");
        break;
    case ERROR_FILE_READ:
        printf("Error: Could not read from file.\n");
        break;
    case ERROR_FILE_WRITE:
        printf("Error: Could not write to file.\n");
        break;
    case ERROR_INVALID_DATA:
        printf("Error: Invalid data format.\n");
        break;
    case ERROR_NOT_FOUND:
        printf("Error: Item not found.\n");
        break;
    case ERROR_EMPTY_COLLECTION:
        printf("Error: Collection is empty.\n");
        break;
    default:
        printf("Error: Unknown error occurred.\n");
        break;
    }
}

void print_student(const Student* student)
{
    printf("ID: %u\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Surname: %s\n", student->surname);
    printf("Group: %s\n", student->group);
    printf("Grades: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%u ", student->grades[i]);
    }
    printf("\nAverage: %.2f\n", student_get_average(student));
    printf("---\n");
}

void print_menu(void)
{
    printf("\n=== Student Management System ===\n");
    printf("1. Search by ID\n");
    printf("2. Search by Surname\n");
    printf("3. Search by Name\n");
    printf("4. Search by Group\n");
    printf("5. Sort by ID\n");
    printf("6. Sort by Surname\n");
    printf("7. Sort by Name\n");
    printf("8. Sort by Group\n");
    printf("9. Write student info by ID to trace file\n");
    printf("10. Write above average students to trace file\n");
    printf("11. Display all students\n");
    printf("0. Exit\n");
    printf("Choose option: ");
}

StatusCode handle_search_by_id(const StudentArray* arr)
{
    unsigned int id;
    printf("Enter student ID: ");
    if (scanf("%u", &id) != 1)
    {
        while (getchar() != '\n');
        return ERROR_INVALID_DATA;
    }
    while (getchar() != '\n');

    StudentArray result;
    StatusCode status = student_array_init(&result);
    if (status != OK)
    {
        return status;
    }

    status = find_students_by_id(arr, id, &result);
    if (status != OK)
    {
        student_array_free(&result);
        return status;
    }

    if (result.count == 0)
    {
        printf("No students found with ID %u\n", id);
    }
    else
    {
        printf("\nFound %zu student(s):\n", result.count);
        for (size_t i = 0; i < result.count; i++)
        {
            print_student(&result.students[i]);
        }
    }

    student_array_free(&result);
    return OK;
}

StatusCode handle_search_by_surname(const StudentArray* arr)
{
    char surname[256];
    printf("Enter surname: ");
    if (scanf("%255s", surname) != 1)
    {
        while (getchar() != '\n');
        return ERROR_INVALID_DATA;
    }
    while (getchar() != '\n');

    StudentArray result;
    StatusCode status = student_array_init(&result);
    if (status != OK)
    {
        return status;
    }

    status = find_students_by_surname(arr, surname, &result);
    if (status != OK)
    {
        student_array_free(&result);
        return status;
    }

    if (result.count == 0)
    {
        printf("No students found with surname '%s'\n", surname);
    }
    else
    {
        printf("\nFound %zu student(s):\n", result.count);
        for (size_t i = 0; i < result.count; i++)
        {
            print_student(&result.students[i]);
        }
    }

    student_array_free(&result);
    return OK;
}

StatusCode handle_search_by_name(const StudentArray* arr)
{
    char name[256];
    printf("Enter name: ");
    if (scanf("%255s", name) != 1)
    {
        while (getchar() != '\n');
        return ERROR_INVALID_DATA;
    }
    while (getchar() != '\n');

    StudentArray result;
    StatusCode status = student_array_init(&result);
    if (status != OK)
    {
        return status;
    }

    status = find_students_by_name(arr, name, &result);
    if (status != OK)
    {
        student_array_free(&result);
        return status;
    }

    if (result.count == 0)
    {
        printf("No students found with name '%s'\n", name);
    }
    else
    {
        printf("\nFound %zu student(s):\n", result.count);
        for (size_t i = 0; i < result.count; i++)
        {
            print_student(&result.students[i]);
        }
    }

    student_array_free(&result);
    return OK;
}

StatusCode handle_search_by_group(const StudentArray* arr)
{
    char group[256];
    printf("Enter group: ");
    if (scanf("%255s", group) != 1)
    {
        while (getchar() != '\n');
        return ERROR_INVALID_DATA;
    }
    while (getchar() != '\n');

    StudentArray result;
    StatusCode status = student_array_init(&result);
    if (status != OK)
    {
        return status;
    }

    status = find_students_by_group(arr, group, &result);
    if (status != OK)
    {
        student_array_free(&result);
        return status;
    }

    if (result.count == 0)
    {
        printf("No students found in group '%s'\n", group);
    }
    else
    {
        printf("\nFound %zu student(s):\n", result.count);
        for (size_t i = 0; i < result.count; i++)
        {
            print_student(&result.students[i]);
        }
    }

    student_array_free(&result);
    return OK;
}

StatusCode handle_sort(StudentArray* arr, ComparatorFunc comparator, const char* sort_type)
{
    StatusCode status = sort_students(arr, comparator);
    if (status != OK)
    {
        return status;
    }

    printf("Students sorted by %s.\n", sort_type);
    return OK;
}

StatusCode handle_write_student_info(const StudentArray* arr, const char* trace_file)
{
    unsigned int id;
    printf("Enter student ID: ");
    if (scanf("%u", &id) != 1)
    {
        while (getchar() != '\n');
        return ERROR_INVALID_DATA;
    }
    while (getchar() != '\n');

    StatusCode status = write_student_info_by_id(arr, id, trace_file);
    if (status == OK)
    {
        printf("Student info written to trace file.\n");
    }

    return status;
}

StatusCode handle_write_above_average(const StudentArray* arr, const char* trace_file)
{
    StatusCode status = write_above_average_students(arr, trace_file);
    if (status == OK)
    {
        printf("Above average students written to trace file.\n");
    }

    return status;
}

void display_all_students(const StudentArray* arr)
{
    if (arr->count == 0)
    {
        printf("No students in the database.\n");
        return;
    }

    printf("\nAll students (%zu):\n", arr->count);
    for (size_t i = 0; i < arr->count; i++)
    {
        print_student(&arr->students[i]);
    }
}
