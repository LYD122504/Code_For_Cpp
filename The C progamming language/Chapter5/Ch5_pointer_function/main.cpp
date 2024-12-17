#include<stdio.h>
#include"sort.h"
char* lineptr[MAXLINES];
int main(int argc, char* argv[]) {

    int nlines;
    int numeric=0;//1 if numeric sort
    if(argc>1&&strcmp(argv[1],"-n")==0)
        numeric=1;
    printf("Please input passage:\n");

    if ((nlines = readline(lineptr, MAXLINES)) >= 0) {
        //qsort(lineptr, 0, nlines - 1);
        qsort(lineptr, 0, nlines - 1, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
        writeline(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}