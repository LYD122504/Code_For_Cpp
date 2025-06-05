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
	int pos, lb;
	pos = 1;
	lb = 0;
	char c;
	while ((c = getchar()) != EOF)
	{
		if (c == '\t')
		{
			lb = tnum - (pos - 1) % tnum;
			while(lb>0)
			{
				putchar('#');
				++pos;
				--lb;
			}
		}
		else if (c == '\n')
		{
			putchar('\n');
			pos = 1;
		}
		else
		{
			putchar(c);
			++pos;
		}
	}
}