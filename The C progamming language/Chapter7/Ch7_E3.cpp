#include <stdio.h>
#include <stdarg.h>
//minprintf:minimal printf with variable argument list
void minprintf(const char *fmt, ...);
  int main()
{
  char *sval =(char*) "10";
    int ival = 11;
    double dval = 12.13;
    unsigned int uival = 14;
    char cval = 'F';
    void *pval = sval;
    minprintf("%%s=%s, %%d=%d, %%i=%i, %%f=%f, %%e=%e, %%E=%E, %%g=%g, %%G=%G, %%o=%o, %%x=%x\n", sval, ival, ival, dval, dval, dval, dval, dval, uival, uival);
       printf("%%s=%s, %%d=%d, %%i=%i, %%f=%f, %%e=%e, %%E=%E, %%g=%g, %%G=%G, %%o=%o, %%x=%x\n", sval, ival, ival, dval, dval, dval, dval, dval, uival, uival);
    minprintf("%%X=%X, %%u=%u, %%c=%c, %%p=%p, %%%%=%%\n", uival, uival, cval, pval);
       printf("%%X=%X, %%u=%u, %%c=%c, %%p=%p, %%%%=%%\n", uival, uival, cval, pval);
}
void minprintf(const char *fmt, ...) {
  //va_list类型表示一种参数指针，用来指代匿名参数
  va_list ap; // points to each unnamed arg in turn
  char *p, *sval;
  int ival;
  double dval;
  unsigned int uval;
  void *pval;
  char format[3]={'%','\0','\0'};
  // va_start是一个宏，其可用来初始化参数指针ap,使之指向第一个匿名参数，其必须在ap使用之前完成初始化
  // 我们要求参数列表中至少要有一个有名参数，va_start将最后一个有名参数作为起点
  va_start(ap, fmt); // make ap point to 1st unnamed arg
  for (p =(char*) fmt; *p; p++) {
	// 如果不是%也就是下一个字符不是占位符
    if (*p != '%') {
      putchar(*p);
	  continue;
    }
    switch (*++p) {
    case 'd':
    case 'i':
    case 'c':
      // 每次调用va_arg,该函数都将返回一个参数，并将ap指向下一个参数。
	  // va_arg使用一个类型名来决定返回的对象类型、指针移动的步长
      ival = va_arg(ap, int);
      format[1] = *p;
      printf(format, ival);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
	  format[1] = *p;
      dval = va_arg(ap, double);
	  printf(format, dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    case 'x':
    case 'X':
    case 'u':
    case 'o':
	  format[1] = *p;
      uval = va_arg(ap, unsigned int);
	  printf(format, uval);
      break;
    case 'p':
      pval = va_arg(ap, void *);
      printf("%p", pval);
	  break;
    case '%':
      putchar('%');
	  break;
    default:
	  putchar('%');
      putchar(*p);
	  break;
	}
  }
  // 必须在函数返回之前调用va_end,以完成一些必要的清理工作
  va_end(ap);//clean up when done
}
