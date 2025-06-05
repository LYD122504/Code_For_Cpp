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
};
struct fnode {
	char* word[MAXWORD];
	int nword;
	int freq;
	struct fnode* left;
	struct fnode* right;
};
struct tnode* addtree(struct tnode*, char*);
struct tnode* talloc(void);
void treeprint(struct tnode*);
char* strup(char*);
int getword(char*, int);
int getch(void);
void ungetch(int);
struct fnode* falloc(void);
struct fnode* addfreq(struct fnode*, struct tnode*);
struct fnode* addword(struct fnode* froot, struct tnode* root);
void freqprint(struct fnode*);

int main()
{
	struct tnode* root;
	char word[MAXWORD];
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
				root = addtree(root,word);
	struct fnode* froot=NULL;
	froot = addfreq(froot, root);
	freqprint(froot);
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
	if ((flag = strcmp(word, root->word)) == 0)
	{
		root->count++;
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
struct fnode* falloc(void)
{
	return (struct fnode*)malloc(sizeof(struct fnode));
}
struct fnode* addfreq(struct fnode* froot, struct tnode* root)
{
	if (root != NULL)
	{
		froot = addword(froot, root);
		addfreq(froot, root->left);
		addfreq(froot, root->right);
	}
	return froot;
}
struct fnode* addword(struct fnode* froot, struct tnode* root)
{
	if (froot == NULL)
	{
		froot = falloc();
		froot->word[0] = root->word;
		froot->nword = 1;
		froot->freq = root->count;
		froot->left = NULL;
		froot->right = NULL;
	}
	else if (froot->freq == root->count)
	{
		froot->word[froot->nword++] = root->word;
	}
	else if (froot->freq < root->count)
	{//word节点频率更大
		froot->right=addword(froot->right, root);
	}
	else
	{
		froot->left=addword(froot->left, root);
	}
	return froot;
}
void freqprint(struct fnode* froot)
{
	if (froot != NULL)
	{
		freqprint(froot->right);
		printf("%4d", froot->freq);
		for (int i = 0; i < froot->nword; i++)
		{
			printf(" %s ", froot->word[i]);
		}
		printf("\n");
		freqprint(froot->left);
	}
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
