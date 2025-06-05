#include<stdio.h>
#include<string.h>
#define MAXLINE 1000

int getline(char* line,int max);

//find: print lines that match pattern from 1st arg
//此处用argv[1]来表示需要匹配的模式串
//文本串则是通过用户输入的

//虽然数组名作为实参是不允许进行自加或自减的操作，形参则实际上是以指针形式表示的，因此可以自加自减
//当数组名作为函数形参时，在函数体内，其失去了本身的内涵，仅仅只是一个指针，而且在函数体内可以作自增、自减等操作，可以被修改
int main(int argc,char* argv[])
{
  char line[MAXLINE];
  char c;
  int expect,number,found;
  int linum;
  linum=0;
  expect=number=found=0;

  while(--argc>0&&*(++argv)[0]=='-')
    while(c=*(++argv[0]))
      switch(c)
		{
		case 'x':
		  expect=1;
		  break;
		case 'n':
		  number=1;
		  break;
		default:
		  printf("find: illegal option %c\n",c);
		  argc=0;
		  found=-1;
		  break;
		}
  if(argc!=1)
    printf("Usage: find -x -n pattern\n");
  else
    while(getline(line,MAXLINE)>0)
      {
		linum++;
		if((strstr(line,*argv)!=NULL)!=expect)
		  {
			if (number)
			  printf("%d:",linum);
			printf("%s",line);
			found++;
		  }
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
