#include<stdio.h>

void squeeze(char s[],int c);
#define maxsize 1000
int main()
{
  char s[maxsize]={};
  char c;
  printf("请输入一个不超过1000字符的字符串\n");
  scanf("%[^\n]",s); 
  getchar();
  printf("请给出想要删除的字符\n");
  scanf("%c",&c);
  squeeze(s,c);
  for(int i=0;s[i]!='\0';i++)
   printf("%c",s[i]);
  printf("\n");
}

// squeeze delete all char c from string s
void squeeze(char s[],int c)
{
  int i,j;
  for (i=j=0;s[i]!='\0';i++)
    if (s[i]!=c)
      {
	s[j++]=s[i];
      }
  s[j]='\0';
}
