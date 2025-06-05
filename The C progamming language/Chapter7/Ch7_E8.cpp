#include <stdio.h>
#include <stdlib.h>

#define MAXHEAD 3
#define MAXTAIL 3
#define MAXLINE 66
#define MAXPAGE 6
#define SINLINE 1000

void fileprint(FILE *fp,char* fname);
int heading(char* fname,int pageno);

int main(int argc, char *argv[]) {
  FILE *fp;
  if (argc == 1)
    fileprint(stdin, (char *)" ");
  else
    while (--argc) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "printf: can't open the file %s.\n", *argv);
        exit(1);
      } else {
        fileprint(fp, *argv);
		fclose(fp);
      }
    }
}
void fileprint(FILE *fp, char *fname) {
  int lineno;
  int pageno = 1;
  char line[SINLINE];
  // 第一页的标题和页码
  lineno = heading(fname, pageno++);
  while (fgets(line, SINLINE, fp)) {
    if (lineno == 1) {
	  if (pageno > MAXPAGE)
            return;
	  fprintf(stdout,"\f");
      lineno = heading(fname, pageno++);
    }
    fputs(line, stdout);
    if (++lineno > MAXLINE - MAXTAIL)
      lineno = 1;
  }
}
int heading(char *fname, int pageno) {
  int ln=3;
  for (int i = 1; i < ln; i++)
    fprintf(stdout, "\n");
  fprintf(stdout, "%s\t page: %d\n", fname, pageno);
  while (ln++ < MAXHEAD)
	fprintf(stdout,"\n");
  return ln;
}
