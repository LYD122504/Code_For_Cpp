#include<stdio.h>

#define maxsize 1000
void squeeze(char s1[],char s2[]);

int main()
{
  char s1[maxsize]={},s2[maxsize]={};
  printf("请输入一个字符串\n");
  scanf("%[^\n]",s1);
  getchar();
  printf("请输入一个想要删除的字符集合\n");
  scanf("%[^\n]",s2);
  squeeze(s1, s2);
  printf("%s",s1);
}
// delete each character in s1 that matches any character in the string s2
void squeeze(char s1[],char s2[])
{
  int i,j,k;
  char c;
  for (i=0; s2[i]!='\0';i++)
    {
      c=s2[i];
      for (j=k=0;s1[j]!='\0';j++)
	if (s1[j]!=c)
	  s1[k++]=s1[j];
      s1[k]='\0';
    }
}
