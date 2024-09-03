#include<stdio.h>
#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);
int strindex(char text[], char pattern[]);

int main()
{
	char pattern[MAXLINE] = "ould";// pattern to search for
	char line[MAXLINE] = "";
	//find all lines matching pattern
	int found = 0;
	int index;
	while (getline(line, MAXLINE) > 0)
		if ((index = strindex(line, pattern)) >= 0)
		{
			found++;
		}
	printf("The most right index of pattern is %d.\n", index);
	printf("Total match times is %d.\n", found);
}
// getline: get line into s, return length
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
// strindex: return index of t in s, -1 if none
int strindex(char text[], char pattern[])
{
	int i, j, k, index = -1;
	for (i = 0; text[i] != '\0'; i++)
	{
		for (j = i, k = 0; pattern[k] != '\0' && text[j] == pattern[k]; j++, k++)
			;
		if (k > 0 && pattern[k] == '\0')
		{
			index = i;
		}
	}
	return index;
}