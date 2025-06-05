#include <stdio.h>
// cat: concatenate files, version1
void filecopy(FILE *fp, FILE *ofp);
int main(int argc, char *argv[]) {
  FILE *fp;
  if (argc == 1)
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*(++argv), "r")) == NULL) {
        printf("cat: can not open %s\n", *argv);
		return 1;
      }else {
		filecopy(fp,stdout);
      }
  return 0;
}

void filecopy(FILE *fp, FILE *ofp) {
  char c;
  while ((c = getc(fp)) != EOF) {
	putc(c,ofp);
  }
}


