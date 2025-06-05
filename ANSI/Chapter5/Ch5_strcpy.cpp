#include<stdio.h>
void strcpy_array(char* s, char* t);
void strcpy_pointer(char* s, char* t);
void strcpy_pointer_v2(char* s, char* t);
int main()
{
	char str[100];
	char array[100];
	printf("请输入需要复制的字符串");
	scanf("%[^\n]%*c", str);
	strcpy_pointer_v2(array, str);
	printf("数组形式复制后的字符串为 %s.\n", array);
}
// strcpy: copy t to s
void strcpy_array(char* s, char* t)
{
	for (int i = 0; (s[i] = t[i]) != '\0'; i++);
}
void strcpy_pointer(char* s, char* t)
{
	int i = 0;
	while ((*(s + i) = *(t + i)) != '\0')
		i++;
}
void strcpy_pointer_v2(char* s, char* t)
{
  while (*s++ = *t++);
}
