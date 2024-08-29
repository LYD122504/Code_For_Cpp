#include<stdio.h>
#define MAXSIZE 200
int main()
{
  int sentence[MAXSIZE]={};
  int e_sentence[MAXSIZE]={};
  int c,i=0,length,j;
  while ((c=getchar())!=EOF&&i<MAXSIZE)
    {
      sentence[i]=c;
      i++;
    }
  length=i;
  for(i=0,j=0;i<=length&&(c=sentence[i])!=EOF;i++)
    {
    switch(c)
      {
    case '\n':
      {
      e_sentence[j++]='\\';
      e_sentence[j++]='n';
      break;
      }
    case '\t':
      {
      e_sentence[j++]='\\';
      e_sentence[j++]='t';
      break;
      }
    default:
      {
      e_sentence[j++]=c;
      break;
      }
      }
    }
    for(i=0;i<=length&&(c=e_sentence[i])!=EOF;i++)
      printf("%c",c);
}
