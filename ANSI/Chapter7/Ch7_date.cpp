#include <stdio.h>
#define MAXWORD 100
int getline(char* line,int lim);
int main() { //读取年月日
  
  // 1st version
  int day, year,month;
  char monthname[20];
  char line[MAXWORD];
  /*
  scanf("%d %s %d", &day, monthname, &year);
  printf("%d %s %d\n", day, monthname, year);
  // 2nd version
  //这里需要的是虽然我们设定的分隔符是/但实际上字符串读取并不会就此停止
  //我们需要在字符串末尾加一个空白以表示其结束
  scanf("%d/%s/%d", &day, monthname, &year);
  printf("%d %s %d\n", day, monthname, year);
  */
  //混合输入的情况
  while (getline(line, MAXWORD)) {
    if (sscanf(line, "%d %s %d", &day, monthname, &year)==3)
      printf("valid: %s\n", line);
    else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
      printf("valid: %s\n", line);
	else
	  printf("invalid:%s\n",line);
  }
}
int getline(char *line, int lim) {
  char c;
  int i = 0;
  while ((c = getchar()) != EOF && i < lim - 1) {
    line[i++] = c;
    if (c == '\n')
      break;
  }
  line[i]='\0';
  return i;
}
