#include <stdio.h>
#include <string.h>
#include <ctype.h>



enum type {
    LOWER, UPPER };

int main(int argc, char *argv[])
{
   
    int c, mode = -1;
    if (strcmp( argv[1], "lower") == 0) 
	{
   
		printf("To lower\n");
        mode = LOWER;		
	}
    else if (strcmp(argv[1], "upper+") == 0) 
	{
		printf("To upper\n");
        mode = UPPER;	
	}		
    if (mode == LOWER)
	{
   
        while ((c = getchar()) != EOF)
            putchar(tolower(c));		
	}
    else if (mode == UPPER)
	{
   
        while ((c = getchar()) != EOF)
            putchar(toupper(c));		
	}
    return 0;
}
