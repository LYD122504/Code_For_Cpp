//逆波兰表达式计算器的多文件编程
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//计算器头文件设置
#include "calc.h"
#define exp_tag 'e'
#define sin_tag 'i'
#define VARIABLE 'x'
#define MAXOP 100
#define MAXLINE 1000 // length of a maximum line to be read
//reverse Polish calculator
int main()
{
	int type,mod_op2;
	double v, op2=0.0;
	char s[MAXOP],line[MAXLINE]="";
	while (getline(line, MAXLINE) > 0)
	while ((type = mod_getop(s,line)) != '\0')
	{
		switch (type)
		{
		case NUMBER:
			v = atof(s);
			push(v);
			break;
		case VARIABLE:
			push(op2);
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
		case '^':
			op2 = pop();
			push(pow(pop(), op2));
			break;
		case sin_tag:
			push(sin(pop()));
			break;
		case exp_tag:
			push(exp(pop()));
			break;
		case '/':
			op2 = pop();
			if (op2)
				push(pop() / op2);
			else
				printf("ERROR: zero divisior.\n");
			break;
		case '%':
			mod_op2 = (int)pop();
			push((int)pop() % mod_op2);
			break;
		case 's':
			printf("\t%.8g\n", show_top());
			break;
		case 'c':
			copy_top();
			op2 = pop();
			printf("\t%.8g\n", op2);
			op2 = pop();
			printf("\t%.8g\n", op2);
			break;
		case 'w':
			swap_top();
			break;
		case 'l':
			clean();
			break;
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
