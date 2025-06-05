#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <malloc.h>

#define MAXWORD 100
#define BUFSIZE 1000
#define MAXGROUPWORD 1000
struct tnode {//the tree node
	char* word;//points to the text
	int count;//numbers of occurrences
	struct tnode* left=NULL;//left child
	struct tnode* right=NULL;//right child
};
//做链表结构
struct gnode {
	char* word;
	struct tnode* list[MAXGROUPWORD];
	int len;
	struct gnode* next=NULL;
};

struct tnode* addtree(struct tnode*, char*);
struct tnode* talloc(void);
struct gnode* galloc(void);
void treeprint(struct tnode*);
char* strup(char*);
int getword(char*, int);
int mod_getch(void);
int getch(void);
void ungetch(int);
void addgroup(struct gnode*, struct tnode*);
struct gnode* add_list(struct gnode*, struct tnode*);
void gprint(struct gnode*);
int len = 4;
int main()
{
	struct tnode* root;
	char word[MAXWORD];
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	struct gnode* groot = galloc();
	groot->word = (char*) "";
	groot->list[0] = NULL;
	groot->len = 0;
	groot->next = NULL;
	addgroup(groot, root);
	gprint(groot);
	return 0;
}
struct tnode* addtree(struct tnode* root, char* word)
{
	if (root == NULL)
	{
		//这里需要做一个remark,虽然我们在结构体里已经设定了一些默认值,但我们这里生成的空间并不是完全依赖于结构体的规则的
		//或者可以认为我们生成的空间其实只是一块空间,这里面的值可能已经存在
		root = talloc();
		root->word=strup(word);
		root->count = 1;
		root->left = root->right = NULL;
		return root;
	}
	int flag;
	if ((flag = strcmp(word,root->word)) == 0)
		root->count++;
	else if (flag > 0)
		root->right = addtree(root->right, word);
	else
		root->left = addtree(root->left, word);
	return root;
}
void addgroup(struct gnode* groot, struct tnode* root)
{
	if (root != NULL)
	{
		addgroup(groot, root->left);
		add_list(groot, root);
		addgroup(groot, root->right);
	}
}
void gprint(struct gnode* groot)
{
	if (groot != NULL)
	{
		if (groot->len > 1)
		{
			printf("%s\n", groot->word);
			for(int i=0;i<groot->len;i++)
				printf("\t%s\n", groot->list[i]->word);
		}
		gprint(groot->next);
	}
}
struct gnode* add_list(struct gnode* groot, struct tnode* root)
{
	char* s;
	s = strdup(root->word);
	s[len] = '\0';
	if (groot == NULL)
	{
		groot = galloc();
		groot->word = s;
		groot->len = 1;
		groot->list[0] = root;
		groot->next = NULL;
		return groot;
	}
	if (strncmp(groot->word, root->word, len) == 0)
	{
		if (groot->len < MAXGROUPWORD)
			groot->list[groot->len++] = root;
		else
			printf("too many word in group");
	}
	else
		groot->next = add_list(groot->next,root);
	return groot;
}
struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
}
struct gnode* galloc(void)
{
	return (struct gnode*)malloc(sizeof(struct gnode));
}
char* strup(char* s)
{
	char* p;
	p = (char*)malloc(strlen(s) + 1);//字符串最后还有一个'\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}
void treeprint(struct tnode* p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
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
int getword(char* word, int lim)
{
	int c;
	char* temp = word;
	while (isspace(c = mod_getch()));
	//如果c不是EOF，那么将c存入temp中
	if (c != EOF)
		*temp++ = c;
	//如果c不是英文字符，那么将temp置为'\0'，并返回c，这样使得一些词组会被拆开，例如1break会被拆成1和break
	if (c != '#' && !isalpha(c))
	{
		*temp = '\0';
		return c;
	}
	//如果c是英文字符，那么将后续的英文和数字字符存入temp中
	for (; --lim > 0; temp++)
	{
		if (!isalnum(*temp = mod_getch()) && *temp != '_')
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
	//不在注释环境的话置1，在的话置0
	int s_flag = 1;
	int m_flag = 1;
	int skip_flag = 1;
	int string_flag = 1;
	int escape = 0;
	while ((c = getch()) != EOF)
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