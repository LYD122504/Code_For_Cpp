#include<stdio.h>
#include<ctype.h>
#define MAXSIZE 200
int atoi(char s[]);
int main()
{
  char s[MAXSIZE]={};
  int n;
  printf("请输入一个数字的字符形式\n");
  for(int i=0;i<MAXSIZE&&(n=getchar())!=EOF;i++)
    s[i]=n;
  n=atoi(s);
  printf("对应的数字的整数形式为%d",n);
}
//atoi: convert s to integer; version 2
//此版本用来跳过数值前的空白字符
int atoi(char s[])
{
  int i,n,sign;
  //isspace(c):如果c为空白字符,则返回非0值;否则则为0值
  for(i=0;isspace(s[i]);i++);//skip white space
  sign=(s[i]=='-')?-1:1;
  if (s[i]=='+'||s[i]=='-')//skip sign
    i++;
  //isdigit(c):如果c为数字字符也就是0-9,则返回非0值,否则则为0值
  for(n=0;isdigit(s[i]);i++)
    n=10*n+(s[i]-'0');
  return sign*n;
}
