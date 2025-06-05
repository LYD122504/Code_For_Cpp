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

int main()
{
	int type,pre_type;
	char temp[MAXTOKEN];
	while (gettoken() != EOF) {
		strcpy(out, token);
		pre_type = tokentype;
		while ((type = gettoken()) != '\n')
		{
			//如果后面出现了（）那么就需要把指针包括进去
			if (pre_type == '*')
			{
				if (type == PARENS || type == BRACKETS)
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			}
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				//sprintf是将输出存储到指定的字符串
			}
			else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else
				printf("invalid input at %s\n", token);
			pre_type = type;
		}
	}
	printf("%s", out);
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