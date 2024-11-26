#include<stdio.h>
//echo: command-line arguments;
int main(int argc,char* argv[])
{
  int i;
  //Based on the array version
  /*for(i=1;i<argc;i++)
    printf("%s%s",argv[i],(i<argc-1)?" ":"");*/
  //Based on the pointer version
  /*while(--argc)
    printf("%s%s",*(++argv),(argc>1)?" ":"");*/
  //Based on the pointer version,2nd
  while(--argc)
      printf((argc>1)?"%s ":"%s",*(++argv));
  printf("\n");
  return 0;
}
