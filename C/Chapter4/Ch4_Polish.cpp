//本程序是逆波兰表达式的单源文件
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h> // for atof()

#define MAXOP 100 // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int getop(char s[]);
double pop();
void push(double);

int main()
{
	int type;
	double v, op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
		case NUMBER:
			v = atof(s);
			push(v);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2)
				push(pop() / op2);
			else
				printf("ERROR: zero divisior.\n");
		case '\n':
			op2 = pop();
			printf("\t%.8g\n", op2);
			break;
		default:
			printf("ERROR: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


#define MAXVAL 100// maximum depth of val stack
int sp = 0; // new free stack position
double val[MAXVAL]; // value stack
// pop: pop and return top value from stack
double pop()
{
	if (sp)
		return val[--sp];
	else
	{
		printf("ERROR: empty stack.\n");
		return 0.0;
	}
}
// push: push f onto value stack
void push(double v)
{
	if (sp < MAXVAL)
		val[sp++] = v;
	else
		printf("ERROR: stack full, can not push %g\n", v);
}
//这里需要用到一个数组来存储缓冲区的内容,原因是如果不去存储缓冲区的内容,那么遇到下一个字母会被直接舍弃,并不会报错
//加了缓冲区则不会随意舍弃缓冲区的内容
int getch(void);
void ungetch(int);
/* getop: get next character or numeric operand*/
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}