#include<stdio.h>
#include<string.h>
#define BUFSIZE 100
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
//从输入区推入一个字符串到缓冲区
void ungets(char s[])
{
	int i = strlen(s);
	while (i > 0)
		ungetch(s[--i]);
}
//如果只有一个字符push back
char last;
int flag = 0;
int mod_getch()
{
	return flag ? last : getchar();
}
void mod_ungetch(int c)
{
	last = c;
	flag = 1;
}
