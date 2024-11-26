#include<stdio.h>
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
// show_top: Õ¹Ê¾Õ»¶¥ÔªËØ
double show_top()
{
	if (sp)
		return val[sp - 1];
	else
	{
		printf("ERROR: empty stack.\n");
		return 0.0;
	}
}
//copy_top: ¸´ÖÆÕ»¶¥ÔªËØ
void copy_top()
{
	if (sp)
	{
		val[sp] = val[sp - 1];
		sp++;
	}
	else
	{
		printf("ERROR: empty stack.\n");
	}
}
//swap_top: ½»»»Õ»¶¥ÔªËØ
void swap_top()
{
	double temp1,temp2;
	switch (sp)
	{
	case 0:
		printf("ERROR: empty stack.\n");
		break;
	case 1:
		break;
	default:
		temp1 = pop();
		temp2 = pop();
		push(temp1);
		push(temp2);
		break;
	}
}
void clean()
{
	sp = 0;
}