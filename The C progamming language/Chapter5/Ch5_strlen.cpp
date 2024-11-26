#include<stdio.h>
#define MAXSIZE 100
int strlen(char* s);
int main()
{
	int len_con, len_ptr, len_arr;
	const char* con = "hello world";// string constant
	char* ptr;
	char arr[MAXSIZE];
	printf("string constant: %s\n", con);
	len_con = strlen((char*)con);
	printf("length of string constant: %d\n", len_con);
	printf("Please input a string: ");
	scanf("%s", arr);
	ptr = arr;
	printf("string of pointer form: %s, string of array form: %s\n", ptr, arr);
	len_ptr = strlen(ptr);
	len_arr = strlen(arr);
	printf("length of string of pointer form: %d, length of string of array form: %d\n", len_ptr, len_arr);
}
// strlen:return length of string s
int strlen(char* s)
{
	int n;
	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}