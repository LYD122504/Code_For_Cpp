#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define BUFSIZE 100
#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS ,FUNCARGS};
char buf[BUFSIZE];//缓冲区
int bufp = 0;//缓冲区空闲的后一位
int tokentype;//最后一个字符的类型: 类型名NAME，括号PARENS，方括号BRACKETS
char token[MAXTOKEN];// 最后一个token的字符串
char name[MAXTOKEN];// 声明的变量名
char datatype[MAXTOKEN]; // 声明的类型名
char qualifierstype[MAXTOKEN];
char out[1000];
const char* qualifiers[] = { "extern", "static", "auto", "register", "const", "volatile", "signed", "unsigned", "short", "long" };

int getch(void);
void ungetch(int c);
int gettoken(void);//用来读取下一个字符
void dcl(void);
void dirdcl(void);
void set_false(void);
int match(char*);
int flag = 0;
int main()
{
	//读取输入
	while (gettoken() != EOF)
	{
		//判断是不是扩展名
		if (match(token))
		{
			strcpy(qualifierstype, strcat(token, " "));
			gettoken();
		}
		else
			qualifierstype[0] = '\0';
		//第一个输入一定是类型名
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
		{
			printf("syntax error\n");
			set_false();
		}
		if (flag)
			flag = 0;
		else
			printf("%s: %s %s%s\n", name, out,qualifierstype, datatype);
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
			if (c == '*')
			{
				ungetch(c);
				return tokentype = '(';
			}
			else
			{
				*p++ = '(';
				for (*p++ = c; (*p++ = getch()) != ')';);
				*p = '\0';
				return tokentype = FUNCARGS;
			}
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
		{
			printf("error: missing )\n");
			set_false();
			return;
		}
	}
	else if (tokentype == NAME)//变量名
		strcpy(name, token);
	else
	{
		printf("error: expected name or (dcl)\n");
		set_false();
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS||type==FUNCARGS)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == FUNCARGS)
		{
			strcat(out, " function ");
			strcat(out, token);
			strcat(out, " returning");
		}
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}
void set_false(void)
{
	int c;
	if (tokentype != '\n')
		while ((c = getch()) != '\n')
			;
	tokentype = '\n';
	flag = 1;
}
int match(char* s)
{
	// 计算有多少元素的方法
	int i, len;
	len = sizeof(qualifiers) / sizeof(qualifiers[0]);
	for (i = 0; i < len; i++) {
		if (strcmp(qualifiers[i], s) == 0) {
			return 1;
		}
	}
	return 0;