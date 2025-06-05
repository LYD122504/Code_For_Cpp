#include<stdio.h>#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define BUFSIZE 100
#define SIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
void ungetch(int c);
int getch();
int getint(int* p);
int main()
{
	int n;
	int array[SIZE];
	int flag;
	for (n = 0; n < SIZE && getint(array + n) != EOF; n++);
	printf("输入的整数形式为： ");
	for (int i = 0; i < n; i++)
		printf("%d ", array[i]);
	printf("\n");
}
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
// getint : get next integer from input into *p
// getint returns EOF for end of file
// getint return 0 if the nexxt input is not a number
// getint return a positive value if the input contains a valid number
int getint(int* p)
{
	int c, sign;
	// skip white space
	while (isspace(c = getch()));
	//not EOF or not number or not sign
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		//值得注意的是这里如果出现字母，那么他会不断的存入缓冲，读取缓冲，不断的循环。
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*p = 0; isdigit(c); c = getch())
	{
		*p = 10 * (*p) + c - '0';
	}
	(*p) *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}