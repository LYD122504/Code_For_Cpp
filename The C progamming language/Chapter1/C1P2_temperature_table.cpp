#include <stdio.h>
/*print Fahrenheit-Celsius table
 for  fahr=0,20,...,300*/

int main()
{
  int fahr,celsius;
  float celsius_float;
  int lower,upper,step;

  lower=0; //lower limit of temperuature scale;
  upper=200; //upper limit
  step=20;// step size

  fahr=lower;
  while (fahr<=upper){
    celsius=5*(fahr-32)/9;
    printf("%d\t%d\n",fahr,celsius);
     celsius_float=(5.0/9.0)*(fahr-32.0);
     printf("%3.0f %6.1f\n",float(fahr),celsius_float);
    fahr=fahr+step;
    }
  return 0;
}
