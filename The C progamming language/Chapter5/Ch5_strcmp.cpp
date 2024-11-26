#include<stdio.h>
#define MAXSIZE 1000
int strcmp_array(char*s, char*t);
int strcmp_pointer(char*s, char*t);
int main()
{
  char p1[MAXSIZE], p2[MAXSIZE];
  int flag;
  printf("请输入需要比较的字符串:");
  scanf("%[^\n]%*c",p1);
  scanf("%[^\n]%*c",p2);
  flag=strcmp_pointer(p1, p2);
  printf("字符串的比较值为 %d.\n",flag);
}
int strcmp_array(char*s,char*t)
{
  int i=0;
  for(;s[i]==t[i];i++)
    if(s[i]=='\0')
      return -t[i];
  return s[i]-t[i];
}
int strcmp_pointer(char*s, char*t)
{
  for(;*s==*t;s++,t++)
    if(*s=='\0')
      return -(*t);
  return *s-(*t);
}
