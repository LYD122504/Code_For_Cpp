#include <stdio.h>
#include <stdarg.h>
//minprintf:minimal printf with variable argument list
void minprintf(char *fmt, ...);
int main() {
  int ival;
  double dval;
  char s[10]="Hello";
  ival = 10;
  dval = 10.245;
  minprintf((char *)"%d\n", ival);
  minprintf((char *)"%f\n", dval);
  minprintf((char *)"%s\n", s);
}
void minprintf(char *fmt, ...) {
  //va_list类型表示一种参数指针，用来指代匿名参数
  va_list ap; // points to each unnamed arg in turn
  char *p, *sval;
  int ival;
  double dval;
  // va_start是一个宏，其可用来初始化参数指针ap,使之指向第一个匿名参数，其必须在ap使用之前完成初始化
  // 我们要求参数列表中至少要有一个有名参数，va_start将最后一个有名参数作为起点
  va_start(ap, fmt); // make ap point to 1st unnamed arg
  for (p = fmt; *p; p++) {
	// 如果不是%也就是下一个字符不是占位符
    if (*p != '%') {
      putchar(*p);
	  continue;
    }
    switch (*++p) {
    case 'd':
      // 每次调用va_arg,该函数都将返回一个参数，并将ap指向下一个参数。
	  // va_arg使用一个类型名来决定返回的对象类型、指针移动的步长
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    default:
      putchar(*p);
	  break;
	}
  }
  // 必须在函数返回之前调用va_end,以完成一些必要的清理工作
  va_end(ap);//clean up when done
}
