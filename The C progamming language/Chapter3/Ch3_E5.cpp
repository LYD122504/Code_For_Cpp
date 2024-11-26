#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXSIZE 200
void reverse(char s[]);
void itob(int n, char* s, int b);
int main()
{
    char s[MAXSIZE] = {};
    int a,b;
    printf("请输入一个数字:");
    scanf("%d", &a);
    printf("请输入进制:");
    scanf("%d", &b);
    itob(a,s,b);
    printf("数字转换的字符串为");
    printf("%s\n", s);
}
void itob(int n, char* s, int b)
{
    int i, sign;
    sign = n;//record sign
    i = 0;
    do {//generate digits in reverse order
      int c=abs(n%b);
      s[i++] =(c>9)?c+'a'-10:c+'0';//get next digit
	} while ((n /= b) != 0);//delete it
    if(sign<0)
		s[i++]='-';
    s[i]= '\0';
    reverse(s);
}
//reverse: reverse string s in place
void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}