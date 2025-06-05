#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char s[]);
double pop();
void push(double);

int main(int argc, char* argv[])
{
	int i,type;
	i = 1;
	double v, op2;
	while (i<argc)
	{
		type = getop(argv[i]);
		switch (type)
		{
		case NUMBER:
			v = atof(argv[i]);
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
		default:
			printf("ERROR: unknown command %s\n", argv[i]);
			break;
		}
		i++;
	}
	op2 = pop();
	printf("\t%.8g\n", op2);
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

int getop(char s[])
{
	int i, c;
	c = *s;
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(*(++s)))
			;
	if (*s == '.') /* collect fraction part */
		while (isdigit(*(++s)))
			;
	*s = '\0';
	return NUMBER;
}