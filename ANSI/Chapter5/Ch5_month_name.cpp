#include<stdio.h>
const char* month_name(int n);
int main()
{
	int n;
	printf("输入月份：");
	scanf("%d", &n);
	printf("%s", month_name(n));
}
const char* month_name(int n)
{
	static const char* name[] = { "Illegal month","January","February","March","April","May","June","July","August","September","October","November","December" };
	return (n < 1 || n>12) ? name[0] : name[n];
}