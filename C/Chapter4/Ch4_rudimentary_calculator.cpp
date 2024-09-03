#include<stdio.h>
#include<ctype.h>
#define MAXLINE 100
int getline(char line[], int maxline);
double atof(char s[]);
int main()
{
	char str[MAXLINE];
	double sum=0;
	printf("Enter a string: ");
	//gets在C语言中虽然可以使用,但需要尽量避免,因为其不会做溢出判断和溢出处理
	//gets(str);
	while(getline(str,MAXLINE))
	{
	  //%g用来输出实数，它根据数值的大小，自动选f格式或e格式（选择输出时占宽度较小的一种），且不输出无意义的0
	  printf("\t%g\n",sum+=atof(str));
	}
	return 0;
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
double atof(char s[])
{
	double value=0.0, pow=1.0;
	int i = 0;
	int sign;
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
		while (isdigit(s[i]))
		{
			value = 10.0 * value + (double)(s[i++] - '0');
			pow = 10.0 * pow;
		}
	}
	return sign * value / pow;
}
