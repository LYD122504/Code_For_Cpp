#include <stdio.h>
int main() {
  int ReturnScanf, ival;
  char cval;
  char sval[10];
  //测试scanf按照input stream读取输入
  /*
  ReturnScanf = scanf("%d", &ival);
  printf("%d\n", ReturnScanf);
  ReturnScanf = scanf("%s%d%c", sval, &ival, &cval);
  printf("%d\n", ReturnScanf);
  printf("%s\t%d\t%c\n", sval, ival, cval);
  */
  //测试scanf的赋值禁止符
  double dval;
  ReturnScanf = scanf("%d%c%lf", &ival, &cval, &dval);
  printf("%d:%d %c %lf\n", ReturnScanf, ival, cval, dval);
  //*会直接掠过这个占位符
  ReturnScanf = scanf("%d%*c%lf", &ival, &dval);
  printf("%d:%d %lf\n", ReturnScanf, ival, dval);
}
