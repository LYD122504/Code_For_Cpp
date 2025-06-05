#include <stdio.h>
#include <stdarg.h>
void minscanf(const char *format, ...);

int main() {
  int a;
  float b;
  char c;
  char s[10];
  minscanf("%d%f%c", &a, &b, &c);
  printf("%d %f %c\n", a, b, c);
  minscanf("%s", s);
  printf("%s\n", s);
}
void minscanf(const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  int *ival;
  char *cval;
  char *sval;
  float *dval;
  char fmt[4]={'%','\0','\0','\0'};
  const char *p;
  for (p = format; *p; p++) {
    if (*p != '%')
      continue;
    switch (*++p) {
    case 'd':
    case 'i':
    case 'c':
      ival = va_arg(ap, int *);
	  fmt[1]=*p;
      scanf(fmt, ival);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
	  fmt[1]=*p;
      dval = va_arg(ap, float *);
      scanf(fmt, dval);
      break;
    case 's':
      fmt[1] = *p;
      sval = va_arg(ap, char *);
      scanf(fmt, sval);
      break;
    }
  }
}
