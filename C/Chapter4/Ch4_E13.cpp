#include<stdio.h>
#include<string.h>
#define MAXSIZE 200
void reverse(char s[]);
int main()
{
    char s[MAXSIZE] = {};
    char c;
    printf("请输入一个字符串:");
    for (int i = 0; i < MAXSIZE && (c = getchar()) != EOF; i++)
        s[i] = c;
    reverse(s);
    printf("反转得到的字符串为");
    printf("%s\n", s);
}
//reverse: reverse string s in place
void reverse(char s[])
{
    int l = strlen(s);
    if (l < 2) return;
    int c1, c2;
    c1 = s[0];
    c2 = s[l - 1];
    s[l - 1] = '\0';
    reverse(s + 1);
    s[0] = c2;
    s[l - 1] = c1;
}