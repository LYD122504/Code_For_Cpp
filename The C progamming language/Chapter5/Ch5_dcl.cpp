#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define BUFSIZE 100
#define MAXTOKEN 100
enum {NAME,PARENS,BRACKETS};
char buf[BUFSIZE];//缓冲区
int bufp = 0;//缓冲区空闲的后一位
int tokentype;//最后一个字符的类型: 类型名NAME，括号PARENS，方括号BRACKETS
char token[MAXTOKEN];// 最后一个token的字符串
char name[MAXTOKEN];// 声明的变量名
char datatype[MAXTOKEN]; // 声明的类型名
char out[1000];

int getch(void);
void ungetch(int c);
int gettoken(void);//用来读取下一个字符
void dcl(void);
void dirdcl(void);

int main()
{
	//读取输入
	while (gettoken() != EOF)
	{
		//第一个输入一定是类型名
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters.\n");
	else
		buf[bufp++] = c;
}
//读取一个token
int gettoken(void)
{
	int c;
	char* p = token;
	//处理空格
	while ((c = getch()) == ' ' || c == '\t');
	//处理括号	
	if (c == '(')
	{
		//完整括号
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		//括号里有内容
		else
		{
			ungetch(c);
			return tokentype = '(';
		}
	}
	//处理方括号
	else if (c == '[')
	{
		for (; (*p++ = c) != ']'; c = getch());
		*p = '\0';
		return tokentype = BRACKETS;
	}
	//处理类型名和变量名
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		ungetch(c);
		*p = '\0';
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}
//dcl的用处是处理指针符号
void dcl(void)
{
	int np;
	for (np = 0; gettoken() == '*'; np++);
	dirdcl();
	while (np--)
		strcat(out, " pointer to");
}
//dirdcl处理的是类型名dirdcl()/dirdcl[]，圆括号(dcl)
void dirdcl(void)
{
	int type;

	if (tokentype == '(')
	{
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME)//变量名
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type == BRACKETS)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}