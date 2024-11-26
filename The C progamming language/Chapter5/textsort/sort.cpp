#include"sort.h"
void qsort(char* lineptr[], int left, int right)
{
    int i, last;
    if (left >= right)
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qsort(lineptr, left, last - 1);
    qsort(lineptr, last + 1, right);
}
void swap(char* v[], int i, int j)
{
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int strcmp(char* s, char* t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return -(*t);
    return *s - (*t);
}
