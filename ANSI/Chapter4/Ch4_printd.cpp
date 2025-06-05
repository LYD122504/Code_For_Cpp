#include<stdio.h>
#include<math.h>
void printd(int n);
int main()
{
    int a;
    printf("请输入一个数字:");
    scanf("%d", &a);
    printf("数字转换的字符串为");
    printd(a);
}
void printd(int n)
{
    int flag = 0;
    if (n < 0)//record sign
    {
        putchar('-');
        n = -n;//make n positive
    }
    if (n / 10 != 0)
        printd(n / 10);
    putchar(abs(n % 10) + '0');
}