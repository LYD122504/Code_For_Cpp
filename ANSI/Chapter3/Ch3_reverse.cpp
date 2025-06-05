#include<stdio.h>
#include<string.h>
#define MAXSIZE 200
void reverse(char s[]);
int main()
{
  char s[MAXSIZE]={};
  char c;
  printf("请输入一个字符串:");
  for(int i=0;i<MAXSIZE&&(c=getchar())!=EOF;i++)
    s[i]=c;
  reverse(s);
  printf("反转得到的字符串为");
  printf("%s\n",s);
}
//reverse: reverse string s in place
void reverse(char s[])
{
  int c,i,j;
  for(i=0,j=strlen(s)-1;i<j;i++,j--)
  {
    c=s[i];
    s[i]=s[j];
    s[j]=c;
  }
}
