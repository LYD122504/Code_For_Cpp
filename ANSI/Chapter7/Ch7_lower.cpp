#include <stdio.h>
#include <ctype.h>
//lower
int main()
{
    int c;
    while((c=getchar())!=EOF)
        putchar(tolower(c));
    return 0;
}