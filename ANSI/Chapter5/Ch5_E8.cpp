#include<stdio.h>
#define YEARDAY 365
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int* month, int* day);
static int daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int main()
{
	int year, month, day, yearday;
	printf("年月日计时转换为总天数:");
	scanf("%d%d%d", &year, &month, &day);
	int leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	if (month > 0 && month < 13 && day >= 0 && day <= daytab[leap][month])
	{
		yearday = day_of_year(year, month, day);
		printf("总天数为 %d.\n", yearday);
	}
	else
		printf("数据输入有误\n");
	printf("年份和总天数转化为月日计时:");
	scanf("%d%d", &year, &yearday);
	if (yearday <= YEARDAY + leap)
	{
		month_day(year, yearday, &month, &day);
		printf("月份为 %d, 日期为 %d.\n", month, day);
	}
	else
		printf("数据输入有误");
}
//day_of_year: set day of year from month and day
int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 0; i < month; i++)
	{
		day += daytab[leap][i];
	}
	return day;
}
// month_day: set month, day from day of year
void month_day(int year, int yearday, int* month, int* day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
	{
		yearday -= daytab[leap][i];
	}
	*month = i;
	*day = yearday;
}