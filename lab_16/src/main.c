#include <stdio.h>

#include "../include/student.h"
#include "../include/functions.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <trace_file>\n", argv[0]);
        return 1;
    }

    const char* input_file = argv[1];
    const char* trace_file = argv[2];

    StudentArray students;
    StatusCode status = student_array_init(&students);
    if (status != OK)
    {
        print_status_error(status);
        return 1;
    }

    status = read_students_from_file(input_file, &students);
    if (status != OK)
    {
        print_status_error(status);
        student_array_free(&students);
        return 1;
    }

    printf("Successfully loaded %zu student(s) from file.\n", students.count);

    int choice;
    int running = 1;

    while (running)
    {
        print_menu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {
        case 1:
            status = handle_search_by_id(&students);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 2:
            status = handle_search_by_surname(&students);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 3:
            status = handle_search_by_name(&students);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 4:
            status = handle_search_by_group(&students);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 5:
            status = handle_sort(&students, compare_by_id, "ID");
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 6:
            status = handle_sort(&students, compare_by_surname, "Surname");
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 7:
            status = handle_sort(&students, compare_by_name, "Name");
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 8:
            status = handle_sort(&students, compare_by_group, "Group");
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 9:
            status = handle_write_student_info(&students, trace_file);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 10:
            status = handle_write_above_average(&students, trace_file);
            if (status != OK)
            {
                print_status_error(status);
            }
            break;

        case 11:
            display_all_students(&students);
            break;

        case 0:
            printf("Exiting program.\n");
            running = 0;
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    }

    student_array_free(&students);
    return 0;
}
