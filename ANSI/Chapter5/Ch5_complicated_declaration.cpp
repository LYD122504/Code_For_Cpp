#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int main()
{
  
}
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{	
	if (buf[bufp - 1] == EOF)
		printf("EOF!");
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
