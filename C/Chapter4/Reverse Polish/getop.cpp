#include<stdio.h>
#include<ctype.h>
#include "calc.h"
/* getop: get next character or numeric operand*/
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c; /* not a number */
	if (c == '-' || c == '+')
	{
		c = getch();
		if (c == ' ' || c == '\t' || c == '\n')
		{
			ungetch(c);
			return s[0];
		}
		s[1] = c;
	}
	
	i = (s[1] == c) ? 1 : 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	ungetch(c);
	return NUMBER;
}
//°´ÕÕÐÐ¶ÁÈ¡
int j = 0;
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && ((c = getchar()) != EOF && c != '\n'))
		s[i++] = c;
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}
int flag1 = 0;
int mod_getop(char s[], char line[])
{
	int c, i;
	if (flag1)
	{
		flag1 = 0;
		return '\n';
	}
	if (line[j] == '\n')
	{
		j++;
		return '\n';
	}
	while (((s[0] = c = line[j++]) != '\0') && (((c == ' ') || (c == '\t'))))
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-' && c != '+')
		return c; /* not a number */
	if (c == '-' || c == '+')
	{
		c = line[j++];
		if (c == ' ' || c == '\t' || c == '\n')
		{
			if (c == '\n')
				flag1 = 1;
			return s[0];
		}
		s[1] = c;
	}

	i = (s[1] == c) ? 1 : 0;
	if (isdigit(c)) /* collect integer part */
		while (isdigit(s[++i] = c = line[j++]))
			;
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = line[j++]))
			;
	s[i] = '\0';
	return NUMBER;
}