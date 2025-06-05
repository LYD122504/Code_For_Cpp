#include<stdio.h>
#define maxsize 1000
void any(char* s1,char* s2);
int main()
{
  char s1[maxsize]={},s2[maxsize]={};
  printf("请输入一个字符串.\n");
  scanf("%[^\n*%c]",s1);
  printf("请输入一个匹配字符的字符集合");
  scanf("%[^\n*%c]",s2);
  
}
// return the first location in a string s1 where any character from the string s2 occurs.
void any(char* s1,char* s2)
{
  char temp;
  for(int i=0;s1[i]!='\0';i++)
    {
     for(int j=0;s2[j]!='\0';j++)
	if (s2[j]==s1[i])
	  {
	    printf("第一个匹配的字符是 %c "
	  }
    }
}
