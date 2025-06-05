#include <stdio.h>
int main() // rudimentary calculator
{
  double sum, v;
  sum = 0;
  //这里用scanf的返回值表示成功赋值的变量个数作为flag,优化了空间存储
  while (scanf("%lf", &v) == 1)
    printf("\t%.2f\n", sum += v);
  return 0;
}
