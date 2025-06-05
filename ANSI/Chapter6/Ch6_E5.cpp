#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define HASHSIZE 101

static struct nlist* hashtab[HASHSIZE];
struct nlist {
	struct nlist* next;
	char* name;
	char* defn;
};

unsigned hash(char* s);
struct nlist* lookup(char* s);
char* strup(char* s);
char* SearchDefn(char* s);
struct nlist* install(char* name, char* defn);
void undef(char* s);
int main(void)
{
	char* name1 = (char*)"IN";
	char* defn1 = (char*)"1";
	char* name2 = (char*)"OUT";
	char* defn2 = (char*)"2";
	char* name3 = (char*)"SOME";
	char* defn3 = (char*)"3";
	char* defn4 = (char*)"4";

	install(name1, defn1);
	install(name2, defn2);
	install(name3, defn3);

	printf("%s is %s\n", name1, SearchDefn(name1));
	printf("%s is %s\n", name2, SearchDefn(name2));
	printf("%s is %s\n", name3, SearchDefn(name3));
	printf("----------\n");
	undef(name2);
	printf("%s is %s\n", name1, SearchDefn(name1));
	printf("%s is %s\n", name2, SearchDefn(name2));
	printf("%s is %s\n", name3, SearchDefn(name3));
	printf("----------\n");
    install(name2, defn4); 
	printf("%s is %s\n", name1, SearchDefn(name1));
	printf("%s is %s\n", name2, SearchDefn(name2));
	printf("%s is %s\n", name3, SearchDefn(name3));
	return 0;
}
void undef(char* s)
{
    struct nlist* np1, * np2;
    unsigned index = hash(s);
    if ((np2 = lookup(s)) == NULL)
        return;
    //判断是不是起始
    np1 = hashtab[index];
    if (np1 == np2)
    {
        hashtab[index] = np1->next;
    }
    else
    {
        for (; np1->next != np2; np1++);
        np1->next = np2->next;
    }
    free(np2->name);
    free(np2->defn);
    free(np2);
    return;
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