#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define MAXWORD 100
#define BUFSIZE 1000
struct key {
	const char* word;
	int count;
}keytab[] = { "auto",0,"break",0,"case",0,"char",0,"const",0,"continue",0,"default",0,"unsigned",0,"void",0,"volatile",0,"while",0 };
int getword(char*, int);
struct key * binsearch(char*, struct key*, int);
int getch(void);
void ungetch(int);
//sizeof是一个编译时运行的单元操作符，其会返回类型或对象占据的字节数
//值得注意的是，其返回结果是无符号整型，但是与unsigned int不同的是这里的类型是size_t，定义在头文件stddef.h中
#define NKEYS sizeof(keytab)/sizeof(key)
//count C keywords
int main()
{
        char word[MAXWORD];
	struct key *p;
	while(getword(word,MAXWORD)!=EOF)
		//因为关键词都是以英文开头的,因此用首字符是否为英文快速筛选一遍，如果不是直接跳转进入下一个循环
		if(isalpha(word[0]))
			if((p=binsearch(word,keytab,NKEYS))!=NULL)
			       p->count++;
	for (p=keytab; p < keytab+NKEYS; p++)
		if (p->count > 0)
			printf("%4d %s\n", p->count, p->word);
	return 0;
}
//binsearch:find word in keytab[0].word, keytab[1].word,...,keytab[n].word
struct key * binsearch(char* word, struct key* tab, int N)
{
	int cond;
	struct key* low=&tab[0];
	struct key* high=&tab[N];
			printf("%4d %s\n", high->count, high->word);
	struct key* mid;
	while (low < high)
	{
	  //这里是因为指针是不能作加法的，high-low 实际上是两者之间相差的元素个数
	  mid = low+(high-low) / 2;
		if ((cond = strcmp(word, mid->word)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
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
	while (isspace(c = getch()));
    //如果c不是EOF，那么将c存入temp中
	if (c != EOF)
		*temp++ = c;
    //如果c不是英文字符，那么将temp置为'\0'，并返回c，这样使得一些词组会被拆开，例如1break会被拆成1和break
	if (!isalpha(c))
	{
		*temp = '\0';
		return c;
	}
    //如果c是英文字符，那么将后续的英文和数字字符存入temp中
	for (; --lim > 0; temp++)
	{
		if (!isalnum(*temp = getch()))
		{
			ungetch(*temp);
			break;
		}
	}
	*temp = '\0';
	return word[0];
}
