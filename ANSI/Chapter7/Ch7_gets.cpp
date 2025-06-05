#include <stdio.h>
#include <stdlib.h>
#define MaxLine 1000

char *fgets(char *s, int n, FILE *iop);
int main() {
  FILE *fp;
  fp = fopen("./test.txt", "r");
  char s[MaxLine];
  if (fp == NULL) {
    printf("Error: Open the file");
	exit(2);
  }
  while (fgets(s, MaxLine, fp) != NULL) {
	puts(s);
  }
  fclose(fp);
  return 0;
}
// fgets: get at most n chars from iop
char *fgets(char *s, int n, FILE *iop) {
  //register 在C++17中已经弃用且不再编译
  int c=0;
  char *cs;
  cs = s;
  //循环判断的两个依据:1.只读取n-1个字符,是因为字符串需要在最后加上一个'\0'作为结尾. 2. 读取到文件的末尾
  while ((--n > 0) && (c = getc(iop)) != EOF)
  {
    if ((*cs++ = c) == '\n')
      break;
  }
  *cs = '\0';
  return (c==EOF&&cs==s)?NULL:s;
}
