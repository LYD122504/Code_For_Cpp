#include<stdio.h>
#define MAXSIZE 1000
void strncpy(char* s, char* t, int n);
void strncat(char* s, char* t, int n);
int strncmp(char* s, char* t, int n);
int strlen(char* s);
int main()
{
	char s[2 * MAXSIZE], t[MAXSIZE];
	int n;
	printf("请输入需要操作的字符串：\n");
	scanf("%[^\n]%*c", s);
	scanf("%[^\n]%*c", t);
	printf("请输入需要限制的字符数为 ");
	scanf("%d", &n);
	//strncpy(s, t, n);
	/*strncat(s, t, n);*/
	n=strncmp(s, t, n);
	//printf("操作结果为 %s\n", s);
	printf("操作结果为 %d\n", n);
}
int strlen(char* s)
{
	char* p = s;
	while (*s != '\0')
		s++;
	return s - p;
}
//把字符串t中的前n个字符拷贝到s中，如果t的字符数小于n，则拷贝到\0为止
void strncpy(char* s, char* t, int n)
{
	int len = strlen(s);
	//如果s太短，需要在末尾加上\0字符
	if (len < n)
		*(s + n) = '\0';
	//开始将t复制到s
	while (*t != '\0' && n--)
		*(s++) = *(t++);
}
void strncat(char* s, char* t, int n)
{
	while (*s != '\0')
		s++;
	while (*t != '\0' && n--)
		*(s++) = *(t++);
	*s = '\0';
}
int strncmp(char* s, char* t, int n)
{
	int i = 0;
	for (; s[i] == t[i] && i != n; i++)
		if (s[i] == '\0')
			return -t[i];
	if (i == n)
		return 0;
	else return s[i] - t[i];
}