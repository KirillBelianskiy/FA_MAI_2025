#pragma once

#include <stdio.h>

#include "status_codes.h"

typedef struct {
    unsigned int id;
    char* name;
    char* surname;
    char* group;
    unsigned char* grades;
} Student;

typedef struct {
    Student* students;
    size_t count;
    size_t capacity;
} StudentArray;

typedef int (*ComparatorFunc)(const void*, const void*);

StatusCode student_array_init(StudentArray* arr);
void student_array_free(StudentArray* arr);
StatusCode student_array_add(StudentArray* arr, const Student* student);

StatusCode student_create(Student* student, unsigned int id, const char* name,
                         const char* surname, const char* group, const unsigned char* grades);
void student_free(Student* student);
StatusCode student_copy(Student* dest, const Student* src);
double student_get_average(const Student* student);

StatusCode validate_string_alpha(const char* str);
StatusCode validate_string_not_empty(const char* str);

StatusCode read_students_from_file(const char* filepath, StudentArray* arr);

StatusCode find_students_by_id(const StudentArray* arr, unsigned int id, StudentArray* result);
StatusCode find_students_by_surname(const StudentArray* arr, const char* surname, StudentArray* result);
StatusCode find_students_by_name(const StudentArray* arr, const char* name, StudentArray* result);
StatusCode find_students_by_group(const StudentArray* arr, const char* group, StudentArray* result);

int compare_by_id(const void* a, const void* b);
int compare_by_surname(const void* a, const void* b);
int compare_by_name(const void* a, const void* b);
int compare_by_group(const void* a, const void* b);

StatusCode sort_students(StudentArray* arr, ComparatorFunc comparator);

StatusCode write_student_info_by_id(const StudentArray* arr, unsigned int id, const char* filepath);
StatusCode write_above_average_students(const StudentArray* arr, const char* filepath);

StatusCode calculate_overall_average(const StudentArray* arr, double* average);