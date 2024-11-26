#include<stdio.h>
#include"sort.h"
char* lineptr[MAXLINES];
int main() {

    int nlines;
    char temp[MAXLINES];
    printf("Please input passage:\n");
    if ((nlines = readline(lineptr,temp, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writeline(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}