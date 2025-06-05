#include"sort.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
void qsort(char* lineptr[], int left, int right, int (*comp)(void*, void*))
{
    int i, last;
    int flag = 1;
    extern int reverse;
    //Excersice 5-14
    if (reverse)
        flag = -1;
    if (left >= right)
        return;
    swap(lineptr, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        //Excersice 5-14
        if ((*comp)(lineptr[i], lineptr[left])*flag < 0)
            swap(lineptr, ++last, i);
    swap(lineptr, left, last);
    qsort(lineptr, left, last - 1, comp);
    qsort(lineptr, last + 1, right, comp);
}
void swap(char* v[], int i, int j)
{
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
int strcmp(char* s, char* t)
{
    extern int fold;
    extern int dict;
    if (dict)
    {
        while (isdigit(*s) && isalpha(*s) && isspace(*s) && *s)
            s++;
        while (isdigit(*t) && isalpha(*t) && isspace(*t) && *t)
            t++;
    }
    if (*s == '\0')
        return -(*t);
    while (fold ? toupper(*s) == toupper(*t) : *s == *t)
    {
        if (*s == '\0')
            return -(*t);
        *s++;
        *t++;
        while (isdigit(*s) && isalpha(*s) && isspace(*s) && *s)
            s++;
        while (isdigit(*t) && isalpha(*t) && isspace(*t) && *t)
            t++;
    }
    return  (fold > 0) ? (toupper(*s) - toupper(*t)) : (*s - *t);
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
int fieldcmp(char* s, char* t)
{
    int i = 0;
    extern int numeric;
    extern int field_pos;
    char p1[BUFSIZ];
    char p2[BUFSIZ];

    while (i < field_pos) {
        if (*s == ',' || *s == '\t')
            i++;
        if (*s == '\0') {
            printf("error : too big %d than field column count\n", field_pos);
            exit(1);
        }
        s++;
    }

    i = 0;
    while (*s != ',' && *s!= '\0')
        p1[i++] = *s++;
    p1[i] = '\0';

    i = 0;
    while (i < field_pos) {
        if (*t == ',' || *t == '\t')
            i++;
        if (*t == '\0') {
            printf( "error : too big %d than field column count\n", field_pos);
            exit(1);
        }
        t++;
    }

    i = 0;
    while (*t != ',' && *t != '\0')
        p2[i++] = *t++;
    p2[i] = '\0';

    return numeric ? numcmp(p1, p2) : strcmp(p1, p2);
}