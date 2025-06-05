#include"sort.h"
#include<stdio.h>
int readline(char* lineptr[], char temp[], int maxlines) {

    int len, nlines;
    char* p=temp, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

void writeline(char* lineptr[], int nlines) {

    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);

    return;
}

int getline(char s[], int lim) {

    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}
void strcpy(char* s, char* t)
{
    while (*s++ = *t++);
}
