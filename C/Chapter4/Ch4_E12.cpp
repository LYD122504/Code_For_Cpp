#include<stdio.h>
#include<math.h>
#define MAXSIZE 200
int printd(int n,char s[],int i);
int main()
{
    int a;
    char s[MAXSIZE];
    printf("请输入一个数字:");
    scanf_s("%d", &a);
    printd(a, s,0);
    printf("数字转换的字符串为");
    printf("%s", s);
}
int printd(int n,char* s, int i)
{
    if (n < 0&&i==0)//record sign
    {
        i++;
        s[0] = '-';
        n = -n;//make n positive
    }
    if (n / 10 != 0)
        i=printd(n / 10,s,i);
    s[i++] = (abs(n % 10) + '0');
    s[i + 1] = '\0';
    return i;
}