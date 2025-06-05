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
  for(i=0,j=0;i<=length&&(sentence[i])!=EOF;i++)
    {
      if(sentence[i]=='\\'&&sentence[i+1]=='t')
	{e_sentence[j++]='\t';i++;}
      else if(sentence[i]=='\\'&&sentence[i+1]=='n')
	{e_sentence[j++]='\n';i++;}
      else {
        e_sentence[j++]=sentence[i];
	  }
    }
    for(i=0;i<=length&&(e_sentence[i])!=EOF;i++)
      printf("%c",e_sentence[i]);
}
