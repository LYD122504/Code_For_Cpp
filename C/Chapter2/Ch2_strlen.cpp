#include<stdio.h>
int strlen(char s[]);
int main()
{
  
  char s[1000]={};
  int length;
  printf("请给出想要计数字符个数的字符串.\n");
  scanf("%s",s);
  length=strlen(s);
  printf("字符串长度为 %d\n",length);
}
// strlen: return the length of char array s
int strlen(char s[])
{
  int i=0;
  while(s[i]!='\0')
    ++i;
  return i;
}
