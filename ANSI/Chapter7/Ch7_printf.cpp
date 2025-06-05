#include <stdio.h>
#include<math.h>
int main()
{
    int d = 3;
    float f=12.14545;
    char s[10]="Hello";
    printf("s=%10.*s\n",d,s);
    printf("d=%19.10d\n", d);
    printf("f=%19f\n", f);
    char str[80];
    sprintf(str, "Pi 的值 = %f", f);
    puts(str);
   
   return(0);
}
