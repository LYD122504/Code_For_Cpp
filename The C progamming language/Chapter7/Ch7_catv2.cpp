#include <stdio.h>
#include <stdlib.h>

// cat:concatenate files, version 2
void filecopy(FILE* fp,FILE*ofp);
int main(int argc, char *argv[]) {
  FILE *fp;
  char *prog=argv[0];
  if (argc == 1) // no argc; copy standard input
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
	  // 虽然数组名是不允许进行加减赋值运算,但是函数的形参其实是以指针的形式存在的
	  if ((fp=fopen(*(++argv),"r"))==NULL) {
		fprintf(stderr,"%s: can't open %s\n", prog,*argv);
		exit(1);
	  }else {
		filecopy(fp, stdout);
		fclose(fp);
	  }
  if (ferror(stdout)) {
	fprintf(stderr, "%s: error writing stdout\n", prog);
	exit(2);
  }
  exit(0);
}
void filecopy(FILE *fp, FILE *ofp) {
  char c;
  while ((c = getc(fp)) != EOF) {
	putc(c,ofp);
  }
}
