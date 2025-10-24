#pragma once

#include "status_codes.h"
#include "student.h"

void print_status_error(StatusCode status);
void print_student(const Student* student);
void print_menu(void);
StatusCode handle_search_by_id(const StudentArray* arr);
StatusCode handle_search_by_surname(const StudentArray* arr);
StatusCode handle_search_by_name(const StudentArray* arr);
StatusCode handle_search_by_group(const StudentArray* arr);
StatusCode handle_sort(StudentArray* arr, ComparatorFunc comparator, const char* sort_type);
StatusCode handle_write_student_info(const StudentArray* arr, const char* trace_file);
StatusCode handle_write_above_average(const StudentArray* arr, const char* trace_file);
void display_all_students(const StudentArray* arr);
