#include<stdio.h>
#include<ctype.h>

#define maxsize 1000
int htoi(char s[]);
int isaf(int c);
int isAF(int c);
int main()
{
  char n[maxsize]={};
  char c;
  printf("请输入一些十六进制的数字.\n");
  scanf("%s",n);
  printf("其对应的十进制数为 %d\n",htoi(n));
}

//htoi converts a string of hexadecimal digits into its equivalent integer value
int htoi(char s[])
{
  int i=0;
  int flag=0;
  int n=0;
  for(;i<maxsize-1&&s[i]!='\0';i++)
    {
      if (s[i]=='0'&& (s[i+1]=='x'||s[i+1]=='X'))
	{
	  flag=1;
	  break;
	}
    }
  if (!flag)
    return -1;
  else
    i+=2;
  while (isdigit(s[i])||isaf(s[i])||isAF(s[i]))
    {
      if(isdigit(s[i]))
	n=16*n+s[i]-'0';
      else if(isaf(s[i]))
	n=16*n+s[i]-'a'+10;
      else if(isAF(s[i]))
	n=16*n+s[i]-'A'+10;
      i=i+1;
    }
  return n;
}
int isaf(int c)
{
  return (c>='a')&&(c<='f');
}
int isAF(int c)
{
  return (c>='A')&&(c<='F');
}
