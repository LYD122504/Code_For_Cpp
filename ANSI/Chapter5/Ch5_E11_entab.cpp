#include <stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	int tnum;
	switch (argc)
	{
	case 1:
		tnum = 8;
		break;
	case 2:
		tnum = atoi(argv[1]);
		break;
	default:
		printf("Usage error\n");
		return 0;
	}
	int spaces=0;
	char c;
	int pos = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			spaces++;
			pos++;
		}
		else if (spaces == 0)//没有空格
		{
			putchar(c);
			spaces = 0;;
		}
		else if (spaces == 1)//一个空格不算制表
		{
			putchar(' ');
			putchar(c);
			spaces = 0;
			pos += 2;
		}
		else
		{
			//如果空格字符让他到下一个制表符的位置那就需要用制表
			while (pos / tnum != (pos + spaces) / tnum)
			{
				putchar('\t');
				pos++;
				spaces--;
				while (pos % tnum != 0)
				{
					pos++;
					spaces--;
				}
			}
			while (spaces > 0) // 仍然有空格字符未处理
			{
				putchar(' ');
				pos++;
				spaces--;
			}
			putchar(c);
			pos++;
		}
		if (c == '\n')
			pos = 0;
	}
}