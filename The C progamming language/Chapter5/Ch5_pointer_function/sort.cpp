#include"sort.h"
#include<stdlib.h>
void qsort(char* lineptr[],int left,int right,int (*comp)(void*, void*))
{
    int i, last;
    if (left >= right)
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if ((*comp)(lineptr[i], lineptr[left]) < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qsort(lineptr, left, last - 1,comp);
    qsort(lineptr, last + 1, right,comp);
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
int numcmp(char* s, char* t)
{
    double a = atof(s);
    double b = atof(t);
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}