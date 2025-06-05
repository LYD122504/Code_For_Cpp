#include<stdio.h>
#include<string.h>
#define MAXLINE 1000

int getline(char* line,int max);

//find: print lines that match pattern from 1st arg
//此处用argv[1]来表示需要匹配的模式串
//文本串则是通过用户输入的
int main(int argc,char* argv[])
{
  char line[MAXLINE];
  int found=0;

  if(argc!=2)
    printf("Usage: find pattern\n");
  else
    while(getline(line,MAXLINE))
      //strstr(s,t): returns a pointer to the first occurrence of the string t in the string s, or NULL if there is none
      if(strstr(line,argv[1])!=NULL)
	{
	  printf("%s",line);
	  found++;
	}
  return found;
}
int getline(char line[], int maxline)
{
	int c, i;
	i = 0;
	while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
		line[i++] = c;
	if (c == '\n')
		line[i++] = c;
	line[i] = '\0';
	return i;
}
