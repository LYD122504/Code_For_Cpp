#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 1000

static struct nlist* hashtab[HASHSIZE];
struct nlist {
	struct nlist* next;
	char* name;
	char* defn;
};

int getword(char*, int);
int getch(void);
void ungetch(int);
unsigned hash(char* s);
struct nlist* lookup(char* s);
char* strup(char* s);
char* SearchDefn(char* s);
struct nlist* install(char* name, char* defn);
int is_legal_char(char);

enum {LABEL,NAME,DEFINITION};
int main(void)
{
	char word[MAXWORD];
	int cond = LABEL;
	char* name=NULL;
	char* defn;
	while (getword(word, MAXWORD) != EOF)
	{
		if (is_legal_char(word[0]))
		{
			if (cond == LABEL && strcmp(word, "#define") == 0)
			{
				cond=NAME;
			}
			else if (cond == NAME)
			{
				name = strup(word);
				cond = DEFINITION;
			}
			else if (cond == DEFINITION)
			{
				defn = strup(word);
				cond = LABEL;
				install(name, defn);
			}
			if (cond == LABEL) {
				printf("%s is %s\n", name, SearchDefn(name));
			}
		}
	}
	return 0;
}

char* SearchDefn(char* s)
{
    struct nlist* np;
    if ((np = lookup(s)) != NULL)
        return np->defn;
    else
        return (char*)"not defined";
}

unsigned hash(char* s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = 31 * hashval + *s;
    return hashval % HASHSIZE;
}

struct nlist* lookup(char* s)
{
    struct nlist* np = hashtab[hash(s)];
    for (; np != NULL; np=np->next )
        if (strcmp(s, np->name) == 0)
            return np;//found
    return NULL;//not found
}

struct nlist* install(char* name, char* defn)
{
	struct nlist* np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL)//not found
	{
		np = (struct nlist*)malloc(sizeof(struct nlist));
		if (np == NULL || (np->name = strup(name)) == NULL)
			//这个判断标准实际上是there is no room for a new entry
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else//found,需要覆盖其已有的值
		free((void*)np->defn);//这里需要注意free(void*),因此我们需要通过强制类型转换使指针变为void*
	if ((np->defn = strup(defn)) == NULL)
		return NULL;
	return np;
}

char* strup(char* s)
{
    char* p;

    p = (char*)malloc(strlen(s) + 1); /* + 1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
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
	if (!is_legal_char(c))
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
int is_legal_char(char c)
{
	if (isalnum(c)) {
		return 1;
	}
	else if (c == '_') {
		return 1;
	}
	else if (c == '#') {
		return 1;
	}
	else if (c == '"') {
		return 1;
	}
	else if (c == '\'') {
		return 1;
	}
	else {
		return 0;
	}
}