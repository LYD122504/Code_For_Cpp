#include<stdio.h>

int atoi(char s[]);
int lower(int c);
int main()
{
  char n[100]={};
  char c;
  printf("输入一个数字的字符形式.\n");
  scanf("%s",n);
  printf("将其转换成整数形式为 %d\n",atoi(n));
  c=getchar();
  printf("输入一个大写字母\n");
  scanf("%c",&c);
  printf("对应的小写字母为 %c\n",lower(c));
}
// atoi: convert s to integer
int atoi(char s[])
{
  int i,n=0;
  for(i=0;s[i]>='0'&&s[i]<='9';++i)
    n=10*n+(s[i]-'0');
  return n;
}

// lower: convert c to lower case; ASCII only
int lower(int c)
{
  if (c>='A'&&c<='Z')
    return 'a'+c-'A';
  else
    return c;
}
