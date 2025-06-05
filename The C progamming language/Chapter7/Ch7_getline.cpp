#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int getline(char *line, int max);
int main() {
  char line[MAXLINE];
  while (getline(line, MAXLINE))
	printf("%s",line);
}
int getline(char *line, int max) {
  if (fgets(line, max, stdin) == NULL)
    return 0;
  else
	return strlen(line);
}
