#include<stdio.h>
#include<ctype.h>
#include<math.h>
#define MAXLINE 100
int getline(char line[], int maxline);
double atoe(char s[]);
int main()
{
  char str[MAXLINE];
  double num;
  printf("Enter a string: ");
  //gets在C语言中虽然可以使用,但需要尽量避免,因为其不会做溢出判断和溢出处理
  //gets(str);
  getline(str,MAXLINE);
  num = atoe(str);
  printf("The number is: %g\n", num);
}
int getline(char line[], int maxline)
{
  int c, i;
  i = 0;
  while (--maxline > 0 && (c = getchar()) != EOF && c != '\n')
    line[i++] = c;
  if (c == '\n')
    line[i++] = c;
  line[i] = '\0';
  return i;
}
double atoe(char s[])
{
  double value=0.0, power=1.0,exp=0.0;
  int i = 0;
  int sign,Exp_sign;
  while (isspace(s[i])) { i++; }
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '-' || s[i] == '+')
    i++;
  while (isdigit(s[i]))
    {
      value = 10.0 * value + (double)(s[i++] - '0');
    }
  if (s[i] == '.')
    {
      i++;
    }
  while (isdigit(s[i]))
    {
      value = 10.0 * value + (double)(s[i++] - '0');
      power = 10.0 * power;
    }
  if(s[i]=='e'||s[i]=='E')
    {
      i++;
      Exp_sign = (s[i] == '-') ? -1 : 1;
      if (s[i] == '-' || s[i] == '+')
	i++;
      while (isdigit(s[i]))
	exp = 10.0 * exp + (double)(s[i++] - '0');
    }
  exp=pow(10.0,Exp_sign*exp);
  return sign * value / power*exp;
}
