#include <climits>
#include<stdio.h>
#include<limits.h>

int main()
{
  printf("There are ranges of signed types\n");
  printf("The min value of char type is %d and the max value of char type is %d\n",CHAR_MIN,CHAR_MAX);
  printf("The min value of short type is %d and the max value of short type is %d\n",SHRT_MIN,SHRT_MAX);
  printf("The min value of int type is %d and the max value of int type is %d\n",INT_MIN,INT_MAX);
  printf("The min value of long type is %ld and the max value of long type is %ld\n",LONG_MIN,LONG_MAX);
  printf("There are ranges of unsigned types\n");
  printf("The max value of unsigned char type is %u\n",UCHAR_MAX);
  printf("The max value of unsigned short type is %u\n",USHRT_MAX);
  printf("The max value of unsigned int type is %lu\n",UINT_MAX);
  printf("The max value of unsigned long type is %llu\n",ULONG_MAX);
  printf("There are bits of different types\n");
  printf("The bits of char type is %d\n",CHAR_BIT);
  printf("The bits of short type is %d\n",SHRT_WIDTH);
  printf("The bits of int type is %d\n",INT_WIDTH);
  printf("The bits of long type is %d\n",LONG_WIDTH);
  printf("The bits of long type is %d\n",LONG_WIDTH);
}
