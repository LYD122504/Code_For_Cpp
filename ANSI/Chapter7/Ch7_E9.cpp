#include <stdio.h>
#define isupper_fast(c) (c>='A'&&c<='Z')?1:0
int isupper_normal(char s);
int main() {
  char c;
  printf("Please input a character:");
  scanf("%c", &c);
  printf("The result is %d\n", isupper_normal(c));
  printf("The result is %d\n", isupper_fast(c));
}
int isupper_normal(char s) {
  if (s >= 'A' && s <= 'Z')
    return 1;
  else
	return 0;
}
