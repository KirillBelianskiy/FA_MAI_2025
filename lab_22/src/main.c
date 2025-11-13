#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Vector.h"

V_T my_string_copy(V_T s)
{
    if (s == NULL) return NULL;
    return strdup(s);
}

void my_string_delete(V_T s)
{
    free(s);
}

int my_string_compare(V_T s1, V_T s2)
{
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL || s2 == NULL) return 1;
    return strcmp(s1, s2);
}

void print_vector(Vector* v)
{
    if (v->size == 0)
    {
        printf("[vector is empty]\n");
        return;
    }

    for (size_t i = 0; i < v->size; i++)
    {
        V_T val = get_at_vector(v, i);
        printf("%s\n", val);
    }
}

int main()
{
    Vector v_str = create_vector(0, my_string_copy, my_string_delete, my_string_compare);

    push_back_vector(&v_str, "First");
    push_back_vector(&v_str, "Second");

    Vector v_str2 = create_vector(5, my_string_copy, my_string_delete, my_string_compare);

    push_back_vector(&v_str2, "First");
    push_back_vector(&v_str2, "Second");

    printf("Are vectors equal? ");
    is_equal_vector(&v_str, &v_str2) ? printf("Yes\n\n") : printf("No\n\n");
    push_back_vector(&v_str, "Second");
    push_back_vector(&v_str, "Third");
    push_back_vector(&v_str, "Forth");

    printf("Are vectors equal? ");
    is_equal_vector(&v_str, &v_str2) ? printf("Yes\n\n") : printf("No\n\n");

    print_vector(&v_str);
    delete_vector(&v_str);
    delete_vector(&v_str2);
    return 0;
}
