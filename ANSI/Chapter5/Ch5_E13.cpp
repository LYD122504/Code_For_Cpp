#include<stdio.h>
#include<stdlib.h>
#define MAXLINES 1000
#define MAXLEN 100
#define ALLOCSIZE 10000
int getline(char s[], int lim);
int readline(char* lineptr[], int maxlines);
void strcpy(char* s, char* t);
char* alloc(int n);
char* lineptr[MAXLINES];
void writeline(char* lineptr[], int nlines,int n);
int main(int argc, char* argv[])
{
    int n;
    if (argc != 2)
    {
        printf("Usage error.\n");
        return 0;
    }
    else if(*argv[1] != '-')
    {
        printf("Usage error.\n");
        return 0;
    }
    n = atoi((argv[1] + 1));
    int nlines;
    if ((nlines = readline(lineptr, MAXLINES)) >= n)
    {
        writeline(lineptr, nlines,n);
        return 0;
    }
    else
    {
        printf("error: input too little\n");
        return 1;
    }
}
int readline(char* lineptr[], int maxlines) {

    int len, nlines;
    char* p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
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
void writeline(char* lineptr[], int nlines,int n) {

    int i;

    for (i = nlines-n; i < nlines; i++)
        printf("%s\n", lineptr[i]);

    return;
}
static char allocbuf[ALLOCSIZE];
static char* allocp = allocbuf;
char* alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
}