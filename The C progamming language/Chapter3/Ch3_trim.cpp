#include<stdio.h>
#include<string.h>
int trim(char s[]);
int main()
{
  char s[20]="test hello     ";
  int len;
  len=trim(s);
  printf("去除末尾空白字符所剩字符个数为 %d\n",len);
}
// trim : remove trailing blanks, tabs, newlines
int trim(char s[])
{
  int n;
  for (n=strlen(s)-1;n>=0;n--)
    if (s[n]!=' '&&s[n]!='\t'&&s[n]!='\n')
      break;
  s[n+1]='\0';
  return n;
}
