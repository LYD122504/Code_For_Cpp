#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

char *fgets(char *s, int n, FILE *ifp);
int fputs(char *s, FILE *ofp);
int main() {
  char s[MAXLINE] = "Hello world";
  FILE *fp = fopen("./test.txt", "w");
  if (fp == NULL) {
    printf("Error: Open the file");
	exit(2);
  }
  fputs(s, fp);
  fclose(fp);
  FILE *ifp = fopen("./test.txt", "r");
  char s1[MAXLINE];
  if (fgets(s1, MAXLINE, ifp) != NULL) {
	puts(s1);
  }
  fclose(ifp);
  return 0;
}
int fputs(char *s, FILE *ofp) {
  int c;
  while (c = *s++)
    putc(c,ofp);
  return ferror(ofp)?EOF:1;
}
char *fgets(char *s, int n, FILE *ifp) {
  int c;
  char *cs;
  cs = s;
  while (--n > 0 && (c = getc(ifp)) != EOF)
    if ((*cs++ = c) == '\n')
      break;
  *cs = '\0';
  return (c == EOF && cs == s) ? NULL : s;
}
