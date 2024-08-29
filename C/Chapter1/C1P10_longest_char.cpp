#include<stdio.h>
int getlines(char line[],int maxsize); // Function Declaration
void swap(char old[],char newline[],int size);
int main()
{
  const int Maxsize=1000;
  int len,max=0; // current line length and maximum line length seen so far
  char newline[Maxsize]={},maxline[Maxsize]={}; // current input line and longest line saved so far
  //Here we use the empty character to initialize the character array 
  while (len=getlines(newline,Maxsize)) // the value of the assignment statement
    if (len>max)
      {
	swap(maxline,newline,len);
	max=len;
      }
  if (max>0)
    printf("The longest line is %s,%d\n",maxline,max);
  else
    printf("There is no line.");
  return 0;
}
int getlines(char line[],int maxsize)
{
  int n=0;
  char c;
  while ((c=getchar())!='\n'&&c!=EOF)
    {
      line[n]=c;
      if ((++n)>(maxsize-1))
	{
	  printf("The size is full");
	  return maxsize;
	}
    }
  return n;
}
void swap(char old[],char newline[],int size)
{
  for(int i=0;i<= size;i++)
    old[i]=newline[i];
}
