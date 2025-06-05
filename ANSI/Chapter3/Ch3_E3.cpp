#include<stdio.h>
#include<string.h>
int isdigit(int c);
int islower(int c);
int isupper(int c);
void expand(char* s1, char* s2);
int main()
{
    char s1[] = "-a-b-c-a-z \n 0-9 \n A-Z- \n a-5 \n h-k";
    char s2[500]={};
    expand(s1, s2);

    printf("%s\n", s2);
}
void expand(char*s1,char*s2)
{
  int i,j;
  s2[0]=s1[0];
  for(i=1,j=1;i<strlen(s1)-1;i++)
    {
      if (s1[i]=='-')
	{
	  int pre=s1[i-1];
	  int back=s1[i+1];
	  if((isdigit(pre)&&isdigit(back))||(islower(pre)&&islower(back))||(isupper(pre)&&isupper(back)))
	    {
	      int sign=(pre<=back)?1:-1;
	      if (sign==1)
		{
		for(int k=pre+1;k<=back;k+=sign)
		  s2[j++]=k;
		i++;
		}
	      else
	       {
		for(int k=pre-1;k>=back;k+=sign)
		  s2[j++]=k;
		i++;
		}
	    }
	  else s2[j++]=s1[i];
	}
      else s2[j++]=s1[i];
    }
}
int isdigit(int c)
{
  return (c>='0'&&c<='9')?1:0;
}
int islower(int c)
{
  return (c>='a'&&c<='z')?1:0;
}
int isupper(int c)
{
  return (c>='A'&&c<='Z')?1:0;
}
