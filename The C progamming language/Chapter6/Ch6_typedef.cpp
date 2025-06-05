#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <malloc.h>

#define MAXWORD 100
#define BUFSIZE 1000


typedef struct tnode {//the tree node
	char* word;//points to the text
	int count;//numbers of occurrences
	struct tnode* left = NULL;//left child
	struct tnode* right = NULL;//right child
} Treenode;
typedef Treenode* Treeptr;

Treeptr addtree(Treeptr, char*);
Treeptr talloc(void);
void treeprint(Treeptr);
char* strup(char*);
int getword(char*, int);
int getch(void);
void ungetch(int);
int main()
{
	Treeptr root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}
//addtree: add a node with word, at or below root
Treeptr addtree(Treeptr root, char* word)
{
	if (root == NULL)// a new word has arrived
	{
		//这里需要做一个remark,虽然我们在结构体里已经设定了一些默认值,但我们这里生成的空间并不是完全依赖于结构体的规则的
		//或者可以认为我们生成的空间其实只是一块空间,这里面的值可能已经存在
		root = talloc(); //make a new node
		root->word = strup(word);
		root->count = 1;
		root->left = root->right = NULL;
		return root;
	}
	int flag;
	if ((flag = strcmp(root->word, word)) == 0)
		root->count++;//repeated word
	else if (flag > 0)//less than into left subtree
		root->right = addtree(root->right, word);
	else//greater than into right subtree
		root->left = addtree(root->left, word);
	return root;
}
//talloc: make a tnode, just  returns a pointer to a free space suitable for holding a tree node, should be initialized by the caller
Treeptr talloc(void)
{
	return (Treeptr)malloc(sizeof(Treenode));
}
char* strup(char* s)
{
	char* p;
	p = (char*)malloc(strlen(s) + 1);//字符串最后还有一个'\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}
//treeprint: in-order print of tree p
void treeprint(Treeptr p)
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