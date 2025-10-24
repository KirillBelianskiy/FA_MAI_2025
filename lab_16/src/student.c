#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/student.h"

#define INITIAL_CAPACITY 10
#define GRADES_COUNT 5

StatusCode student_array_init(StudentArray* arr)
{
    if (arr == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    arr->students = (Student*)malloc(INITIAL_CAPACITY * sizeof(Student));
    if (arr->students == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }

    arr->count = 0;
    arr->capacity = INITIAL_CAPACITY;
    return SUCCESS;
}

void student_array_free(StudentArray* arr)
{
    if (arr == NULL)
    {
        return;
    }

    for (size_t i = 0; i < arr->count; i++)
    {
        student_free(&arr->students[i]);
    }

    free(arr->students);
    arr->students = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

StatusCode student_array_add(StudentArray* arr, const Student* student)
{
    if (arr == NULL || student == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    if (arr->count >= arr->capacity)
    {
        size_t new_capacity = arr->capacity * 2;
        Student* new_students = (Student*)realloc(arr->students, new_capacity * sizeof(Student));
        if (new_students == NULL)
        {
            return ERROR_MEMORY_ALLOCATION;
        }
        arr->students = new_students;
        arr->capacity = new_capacity;
    }

    StatusCode status = student_copy(&arr->students[arr->count], student);
    if (status != SUCCESS)
    {
        return status;
    }

    arr->count++;
    return SUCCESS;
}

StatusCode student_create(Student* student, unsigned int id, const char* name,
                          const char* surname, const char* group, const unsigned char* grades)
{
    if (student == NULL || name == NULL || surname == NULL || group == NULL || grades == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    StatusCode status;

    status = validate_string_alpha(name);
    if (status != SUCCESS)
    {
        return status;
    }

    status = validate_string_alpha(surname);
    if (status != SUCCESS)
    {
        return status;
    }

    status = validate_string_not_empty(group);
    if (status != SUCCESS)
    {
        return status;
    }

    student->id = id;

    student->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    if (student->name == NULL)
    {
        return ERROR_MEMORY_ALLOCATION;
    }
    strcpy(student->name, name);

    student->surname = (char*)malloc((strlen(surname) + 1) * sizeof(char));
    if (student->surname == NULL)
    {
        free(student->name);
        return ERROR_MEMORY_ALLOCATION;
    }
    strcpy(student->surname, surname);

    student->group = (char*)malloc((strlen(group) + 1) * sizeof(char));
    if (student->group == NULL)
    {
        free(student->name);
        free(student->surname);
        return ERROR_MEMORY_ALLOCATION;
    }
    strcpy(student->group, group);

    student->grades = (unsigned char*)malloc(GRADES_COUNT * sizeof(unsigned char));
    if (student->grades == NULL)
    {
        free(student->name);
        free(student->surname);
        free(student->group);
        return ERROR_MEMORY_ALLOCATION;
    }
    memcpy(student->grades, grades, GRADES_COUNT * sizeof(unsigned char));

    return SUCCESS;
}

void student_free(Student* student)
{
    if (student == NULL)
    {
        return;
    }

    free(student->name);
    free(student->surname);
    free(student->group);
    free(student->grades);

    student->name = NULL;
    student->surname = NULL;
    student->group = NULL;
    student->grades = NULL;
}

StatusCode student_copy(Student* dest, const Student* src)
{
    if (dest == NULL || src == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    return student_create(dest, src->id, src->name, src->surname, src->group, src->grades);
}

double student_get_average(const Student* student)
{
    if (student == NULL || student->grades == NULL)
    {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < GRADES_COUNT; i++)
    {
        sum += student->grades[i];
    }

    return sum / GRADES_COUNT;
}

StatusCode validate_string_alpha(const char* str)
{
    if (str == NULL || str[0] == '\0')
    {
        return ERROR_INVALID_DATA;
    }

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha((unsigned char)str[i]))
        {
            return ERROR_INVALID_DATA;
        }
    }

    return SUCCESS;
}

StatusCode validate_string_not_empty(const char* str)
{
    if (str == NULL || str[0] == '\0')
    {
        return ERROR_INVALID_DATA;
    }

    return SUCCESS;
}

StatusCode read_students_from_file(const char* filepath, StudentArray* arr)
{
    if (filepath == NULL || arr == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    FILE* file = fopen(filepath, "r");
    if (file == NULL)
    {
        return ERROR_FILE_OPEN;
    }

    unsigned int id;
    char name[256];
    char surname[256];
    char group[256];
    unsigned char grades[GRADES_COUNT];

    while (fscanf(file, "%u %255s %255s %255s", &id, name, surname, group) == 4)
    {
        int valid_read = 1;
        for (int i = 0; i < GRADES_COUNT; i++)
        {
            unsigned int grade_temp;
            if (fscanf(file, "%u", &grade_temp) != 1)
            {
                valid_read = 0;
                break;
            }
            grades[i] = (unsigned char)grade_temp;
        }

        if (!valid_read)
        {
            fclose(file);
            return ERROR_FILE_READ;
        }

        Student student;
        StatusCode status = student_create(&student, id, name, surname, group, grades);
        if (status != SUCCESS)
        {
            fclose(file);
            return status;
        }

        status = student_array_add(arr, &student);
        student_free(&student);

        if (status != SUCCESS)
        {
            fclose(file);
            return status;
        }
    }

    fclose(file);
    return SUCCESS;
}

StatusCode find_students_by_id(const StudentArray* arr, unsigned int id, StudentArray* result)
{
    if (arr == NULL || result == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < arr->count; i++)
    {
        if (arr->students[i].id == id)
        {
            StatusCode status = student_array_add(result, &arr->students[i]);
            if (status != SUCCESS)
            {
                return status;
            }
        }
    }

    return SUCCESS;
}

StatusCode find_students_by_surname(const StudentArray* arr, const char* surname, StudentArray* result)
{
    if (arr == NULL || surname == NULL || result == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < arr->count; i++)
    {
        if (strcmp(arr->students[i].surname, surname) == 0)
        {
            StatusCode status = student_array_add(result, &arr->students[i]);
            if (status != SUCCESS)
            {
                return status;
            }
        }
    }

    return SUCCESS;
}

StatusCode find_students_by_name(const StudentArray* arr, const char* name, StudentArray* result)
{
    if (arr == NULL || name == NULL || result == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < arr->count; i++)
    {
        if (strcmp(arr->students[i].name, name) == 0)
        {
            StatusCode status = student_array_add(result, &arr->students[i]);
            if (status != SUCCESS)
            {
                return status;
            }
        }
    }

    return SUCCESS;
}

StatusCode find_students_by_group(const StudentArray* arr, const char* group, StudentArray* result)
{
    if (arr == NULL || group == NULL || result == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i < arr->count; i++)
    {
        if (strcmp(arr->students[i].group, group) == 0)
        {
            StatusCode status = student_array_add(result, &arr->students[i]);
            if (status != SUCCESS)
            {
                return status;
            }
        }
    }

    return SUCCESS;
}

int compare_by_id(const void* a, const void* b)
{
    const Student* student_a = a;
    const Student* student_b = b;

    if (student_a->id < student_b->id) return -1;
    if (student_a->id > student_b->id) return 1;
    return 0;
}

int compare_by_surname(const void* a, const void* b)
{
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;

    return strcmp(student_a->surname, student_b->surname);
}

int compare_by_name(const void* a, const void* b)
{
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;

    return strcmp(student_a->name, student_b->name);
}

int compare_by_group(const void* a, const void* b)
{
    const Student* student_a = (const Student*)a;
    const Student* student_b = (const Student*)b;

    return strcmp(student_a->group, student_b->group);
}

StatusCode sort_students(StudentArray* arr, ComparatorFunc comparator)
{
    if (arr == NULL || comparator == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    if (arr->count == 0)
    {
        return ERROR_EMPTY_COLLECTION;
    }

    qsort(arr->students, arr->count, sizeof(Student), comparator);
    return SUCCESS;
}

StatusCode write_student_info_by_id(const StudentArray* arr, unsigned int id, const char* filepath)
{
    if (arr == NULL || filepath == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    FILE* file = fopen(filepath, "a");
    if (file == NULL)
    {
        return ERROR_FILE_OPEN;
    }

    int found = 0;
    for (size_t i = 0; i < arr->count; i++)
    {
        if (arr->students[i].id == id)
        {
            found = 1;
            double average = student_get_average(&arr->students[i]);

            if (fprintf(file, "Student ID: %u\nFull Name: %s %s\nGroup: %s\nAverage Grade: %.2f\n\n",
                        arr->students[i].id,
                        arr->students[i].surname,
                        arr->students[i].name,
                        arr->students[i].group,
                        average) < 0)
            {
                fclose(file);
                return ERROR_FILE_WRITE;
            }
        }
    }

    fclose(file);

    if (!found)
    {
        return ERROR_NOT_FOUND;
    }

    return SUCCESS;
}

StatusCode calculate_overall_average(const StudentArray* arr, double* average)
{
    if (arr == NULL || average == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    if (arr->count == 0)
    {
        return ERROR_EMPTY_COLLECTION;
    }

    double sum = 0.0;
    for (size_t i = 0; i < arr->count; i++)
    {
        sum += student_get_average(&arr->students[i]);
    }

    *average = sum / arr->count;
    return SUCCESS;
}

StatusCode write_above_average_students(const StudentArray* arr, const char* filepath)
{
    if (arr == NULL || filepath == NULL)
    {
        return ERROR_INVALID_ARGUMENT;
    }

    double overall_average;
    StatusCode status = calculate_overall_average(arr, &overall_average);
    if (status != SUCCESS)
    {
        return status;
    }

    FILE* file = fopen(filepath, "a");
    if (file == NULL)
    {
        return ERROR_FILE_OPEN;
    }

    if (fprintf(file, "Students with above average grades (overall average: %.2f):\n", overall_average) < 0)
    {
        fclose(file);
        return ERROR_FILE_WRITE;
    }

    const double eps = 1e-12;
    for (size_t i = 0; i < arr->count; i++)
    {
        double student_avg = student_get_average(&arr->students[i]);
        if ((student_avg - overall_average) > eps)
        {
            if (fprintf(file, "%s %s (%.2f)\n",
                        arr->students[i].surname,
                        arr->students[i].name,
                        student_avg) < 0)
            {
                fclose(file);
                return ERROR_FILE_WRITE;
            }
        }
    }

    if (fprintf(file, "\n") < 0)
    {
        fclose(file);
        return ERROR_FILE_WRITE;
    }

    fclose(file);
    return SUCCESS;
}
