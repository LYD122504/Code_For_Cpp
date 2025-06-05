#include<stdio.h>
#define MAXSIZE 1000
int strend(char*s,char*t);
int strlen(char*s);
int main()
{
  char s[MAXSIZE],t[MAXSIZE];
  printf("请输入查找所在的文本串:\n");
  scanf("%[^\n]%*c",s);
  printf("请输入查找的模式串:\n");
  scanf("%[^\n]%*c",t);
  int flag;
  flag=strend(s,t);
  printf("模式串在文本串的标识为 %d",flag);
}
int strend(char*s,char*t)
{
  int len=strlen(t);
  while(*(s++)!='\0');
  s=s-len-1;
  while(*s==*t&&*t!='\0')
    {
      s++;
      t++;
    }
  if(*t=='\0')
    return 1;
  else return 0;
}
int strlen(char*s)
{
  char*p=s;
  while(*(s++)!='\0');
  s=s-1;
  return s-p;
}
