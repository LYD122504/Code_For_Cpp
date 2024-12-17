#include<stdio.h>
#include<stdlib.h>
#include"sort.h"
char* lineptr[MAXLINES];
int numeric = 0;//1 if numeric sort
//Ex 5-14
int reverse = 0;
int fold = 0;
int dict = 0;
int field = 0;
int field_pos = 0;
int main(int argc, char* argv[]) {

    int nlines;

    char c = 0;;
    int i = 1;
   while(--argc>0&&(*++argv)[0]=='-')
       while(c=*++argv[0])
           switch (c)
           {
           case 'n':
               numeric = 1;
               break;
           case 'r':
               reverse = 1;
               break;
           case 'f':
               fold = 1;
               break;
           case 'd':
               dict = 1;
               break;
           case 'e':
               field = 1;
               field_pos = atoi(++*(argv));
               while (*++argv[0] != '\0')
                   ;
               --argv[0];
               break;
           }
   printf("%d", numeric);
    printf("Please input passage:\n");

    if ((nlines = readline(lineptr, MAXLINES)) >= 0) {
        //qsort(lineptr, 0, nlines - 1);
        qsort(lineptr, 0, nlines - 1, (int (*)(void*, void*)) (field ? fieldcmp : (numeric ? numcmp : strcmp));
        writeline(lineptr, nlines);
        return 0;
    }
    else {
        printf("error: input too big to sort\n");
        return 1;
    }
}