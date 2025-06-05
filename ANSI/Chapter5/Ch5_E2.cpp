//这个版本是为了处理输入字母以后可以跳过字母寻找后面数字的
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define BUFSIZE 100
#define SIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
void ungetch(int c);
int getch();
int getfloat(double* p);
int main()
{
	int n;
	double array[SIZE];
	int flag;
	//flag 用来判断是否找到了一个非数字的值，如果找到了，那么我们将这个值丢弃并且不会向后移动指针
	for (n = 0; n < SIZE && (flag = getfloat(array + n)) != EOF; (flag == 0) ? n : n++);
	printf("输入的整数形式为： ");
	for (int i = 0; i < n; i++)
		printf("%f ", array[i]);
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
int getfloat(double* p)
{
	char c;
	int sign;
	double pow = 1.0;
	// skip white space
	while (isspace(c = getch()));
	//not EOF or not number or not sign
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	if (!isdigit(c) && c != EOF)
	{
		ungetch((sign == -1) ? '-' : '+');
		return 0;
	}
	for (*p = 0; isdigit(c); c = getch())
	{
		*p = 10.0 * (*p) + c - '0';
	}
	if (c == '.')
	{
		pow = 1.0;
		c = getch();
		for (; isdigit(c); c = getch())
		{
			*p = 10.0 * (*p) + c - '0';
			pow *= 10.0;
		}
	}
	*p = sign * (*p) / pow;
	if (c != EOF)
		ungetch(c);
	return c;
}