#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAXWORD 100
#define BUFSIZE 1000
struct key {
	const char* word;
	int count;
}keytab[] = {
	{ "#define", 0},
	{ "#include", 0},
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	{ "double", 0},
	{ "int", 0 },
	/* ... */
	{ "return", 0 },
	{ "size_t", 0 },
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 }
};
int getword(char*, int);
int binsearch(char*, struct key*, int);
int getch(void);
int mod_getch(void);
void ungetch(int);
//sizeof是一个编译时运行的单元操作符，其会返回类型或对象占据的字节数
//值得注意的是，其返回结果是无符号整型，但是与unsigned int不同的是这里的类型是size_t，定义在头文件stddef.h中
#define NKEYS sizeof(keytab)/sizeof(key)
//count C keywords
int main()
{
	//n用来存储找到的数组的index
	int n;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
		//因为关键词都是以英文开头的,因此用首字符是否为英文快速筛选一遍，如果不是直接跳转进入下一个循环
		if (isalpha(word[0]) || word[0] == '#')
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}
//binsearch:find word in keytab[0].word, keytab[1].word,...,keytab[n].word
int binsearch(char* word, struct key* tab, int N)
{
	int cond;
	int low, high, mid;
	low = 0;
	high = N - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
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
//getword: get next word or character from input
int getword(char* word, int lim)
{
	int c;
	char* temp = word;
	while (isspace(c = mod_getch()));
	//如果c不是EOF，那么将c存入temp中
	if (c != EOF)
		*temp++ = c;
	//如果c不是英文字符，那么将temp置为'\0'，并返回c，这样使得一些词组会被拆开，例如1break会被拆成1和break
	if (c!='#'&&!isalpha(c))
	{
		*temp = '\0';
		return c;
	}
	//如果c是英文字符，那么将后续的英文和数字字符存入temp中
	for (; --lim > 0; temp++)
	{
		if (!isalnum(*temp = mod_getch())&&*temp != '_')
		{
			ungetch(*temp);
			break;
		}
	}
	*temp = '\0';
	return word[0];
}
//对读取字符引入跳过机制，主要针对1.空白字符，2.//引导的一行的注释，3./* */引导的多行注释
//这里值得注意的是多行注释之间是不存在嵌套的，单行注释的终点还是换行符，虽然多行注释是可以嵌套单行注释但是其终止依旧是依赖于*/
//这里处理的字符串是用“”的但是值得注意的一点在于，字符串中会出现\"的转义符，需要排除这个情况
int mod_getch(void)
{
	int c;
	int temp;
	//不在注释环境的话置1，在的话置0
	int s_flag = 1;
	int m_flag = 1;
	int skip_flag = 1;
	int string_flag = 1;
	int escape=0;
	while ((c = getch())!=EOF)
	{
		switch (c)
		{
		case '/':
			if (s_flag && m_flag)
			{
				c = getch();
				if (c == '/')
				{
					s_flag = 0;
					skip_flag = 0;
				}
				else if (c == '*')
				{
					m_flag = 0;
					skip_flag = 0;
				}
				else
				{
					ungetch(c);
					return c;
				}
			}
			escape = 0;
			break;
		case '*':
			if (skip_flag)
				return c;
			else if (!m_flag)
			{
				c = getch();
				if (c == '/')
				{
					m_flag = 1;
					skip_flag = 1;
					c = getch();
				}
				else
					ungetch(c);
			}
			escape = 0;
			break; 
		case '\n':
			if (skip_flag)
				return c;
			else if (!s_flag)
			{
				s_flag = 1;
				skip_flag = 1;
			}
			escape = 0;
			break;
		case '\\':
			escape = 1;
			break;
		case '"':
			if (!escape)
			{
				if (string_flag)
				{
					string_flag = 0;
					skip_flag = 0;
				}
				else
				{
					string_flag = 1;
					skip_flag = 1;
				}
			}
			escape = 0;
			break;
		default:
			escape = 0;
			break;
		}
		if (skip_flag)
			return c;
	}
}
