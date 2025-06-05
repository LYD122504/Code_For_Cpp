#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <malloc.h>

#define MAXWORD 100
#define MAXLINE 1024
#define BUFSIZE 1000
#define MAXGROUPWORD 1000
struct tnode {//the tree node
	char* word;//points to the text
	int count;//numbers of occurrences
	struct tnode* left=NULL;//left child
	struct tnode* right=NULL;//right child
	struct lnode* lines = NULL;
};
struct lnode {
	struct tnode* TreePtr;
	int lines[MAXLINE];
	int count;
};
struct tnode* addtree(struct tnode*, char*);
struct tnode* talloc(void);
void treeprint(struct tnode*);
char* strup(char*);
int getword(char*, int);
int getch(void);
void ungetch(int);
int judge_noise(char*);
char* lower(char* word);
struct lnode* addline(struct tnode*, struct lnode*);
struct lnode* lalloc(void);
void lineprint(struct lnode* l);

int NumberLine = 1;
int main()
{
	struct tnode* root;
	char word[MAXWORD];
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if (judge_noise(word))
				root = addtree(root,word);
	treeprint(root);
	return 0;
}
int judge_noise(char* word)
{
	const char* noize_word[] = { "the", "and", "be", "is", "are", "am", "were", "in", "on", "of", "a" };
	int len = sizeof(noize_word) / sizeof(noize_word[0]);
	for (int i = 0; i < len; i++)
	{
		if (strcmp(lower(word), noize_word[i]) == 0)
			return 0;
	}
	return 1;
}
char* lower(char* word)
{
	char* p = word;
	while (*word)
	{
		*word = tolower(*word);
		word++;
	}
	return p;
}
struct lnode* addline(struct tnode* root, struct lnode* line)
{
	if (line == NULL)
	{
		line = lalloc();
		line->TreePtr = root;
		line->lines[0] = NumberLine;
		line->count = 1;
	}
	else if (line->lines[line->count - 1] != NumberLine)
		line->lines[line->count++] = NumberLine;
	return line;
}
struct lnode* lalloc(void)
{
	return (struct lnode*)malloc(sizeof(struct lnode));
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
		root->lines = addline(root, NULL);
		return root;
	}
	int flag;
	if ((flag = strcmp(word, root->word)) == 0)
	{
		root->count++;
		addline(root, root->lines);
	}
	else if (flag > 0)
		root->right = addtree(root->right, word);
	else
		root->left = addtree(root->left, word);
	return root;
}
struct tnode* talloc(void)
{
	return (struct tnode*)malloc(sizeof(struct tnode));
}
char* strup(char* s)
{
	char* p;
	p = (char*)malloc(strlen(s) + 1);//字符串最后还有一个'\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}
void lineprint(struct lnode* l)
{
	printf("\tLines: ");
	for (int i = 0; i < l->count; i++)
		printf("%d%c", l->lines[i], (i == l->count - 1) ? ' ' : ',');
	printf("\n");
}
void treeprint(struct tnode* p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		lineprint(p->lines);
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
//getword: get next word or character from input
int getword(char* word, int lim)
{
	int c;
	char* temp = word;
	while (isspace(c = getch()))
	{
		if (c == '\n')
			NumberLine++;
	};
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
