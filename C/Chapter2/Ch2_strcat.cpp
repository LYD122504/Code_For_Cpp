#include<stdio.h>
#define maxsize 1000

void strcat(char s[],char t[]);
int main()
{
  char s[2*maxsize]={};
  char t[maxsize]={};
  printf("请给出一个字符串\n");
  scanf("%[^\n]",s);
  getchar();
  printf("请给出一个拼接的字符串\n");
  scanf("%[^\n]",t);
  strcat(s,t);
  printf("%s",s);
}

void strcat(char s[],char t[])
{
  int i,j;
  i=j=0;
  while(s[i]!='\0')//find the end of s
   i++;
  while(t[j]!='\0')
    s[i++]=t[j++];//copy t;
}
