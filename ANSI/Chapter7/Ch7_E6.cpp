#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void filecmp(FILE *fp1,FILE *fp2);
int main() {
  FILE *fp1, *fp2;
  fp1 = fopen("./test.txt", "r");
  fp2 = fopen("./test1.txt", "r");
  //判断文件打开情况
  if (fp1 == NULL) {
    printf("Error: Open test.txt");
	exit(1);
  } else if (fp2 == NULL) {
    printf("Error: Open test1.txt");
	exit(2);
  }
  filecmp(fp1, fp2);
  fclose(fp1);
  fclose(fp2);
}
void filecmp(FILE *fp1, FILE *fp2) {
  char s1[MAXLINE], s2[MAXLINE];
  char *sp1, *sp2;
  //如果在fp1和fp2都没有出现读取错误
  while ((sp1 = fgets(s1, MAXLINE, fp1)) && (sp2 = fgets(s2, MAXLINE, fp2))) {
    if (strcmp(s1, s2)) {
      printf("The first different sentence in File one: %s\n", s1);
      printf("The first different sentence in File two: %s\n", s2);
	  return;
	}
  }
  //这种情况是fp1出现了读取结束或者读取错误;但是fp2的读取是正常的.
  if (sp1 == NULL && sp2 == s2) {
    printf("The first different sentence in File two: %s\n", s2);
	return;
  }
  if (sp1 == s1 && sp2 == NULL) {
	 printf("The first different sentence in File one: %s\n", s1);
	return;
  }
}
