#include <stdio.h>
int main()
{
  //count characters in input; 1st version
  long nc=0;
  while (getchar()!=EOF)
    ++nc;
  printf("%ld\n",nc);
  //count characters in input; 2nd version
  double num;
  for(num=0;getchar()!=EOF;++num)
    ;
  printf("%.0f\n",num);
}
