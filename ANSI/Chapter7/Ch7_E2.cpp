#include <stdio.h>
#include <ctype.h>

#define MaxWord 10
#define Local "%x"

int main() {
  int ch, num=0;
  while ((ch = getchar()) != EOF) {
    if (ch == '\n')
      num = 0;
    else if (++num == MaxWord) {
      num = 0;
	  putchar(ch);
      printf("\n");
	  continue; 
    }
    if (isgraph(ch)||isspace(ch))
      printf("%c", ch);
    else
	  printf(Local,ch);
  }
}
