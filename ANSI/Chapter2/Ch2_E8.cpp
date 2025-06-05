#include<stdio.h>
int len(unsigned x);
unsigned rightrot(unsigned x, int n);
int main()
{
	unsigned x = 12345;
	int n = 3;
	printf("%u", rightrot(x, n));
}
int len(unsigned x)
{
	int i = 0;
	for (; x != 0; x >>=1)i++;
	return i;
}
unsigned rightrot(unsigned x, int n)
{
	int length = len(x);
	/*for (int i = 1; i <= n; i++)
	{
		unsigned temp = (x & 1) << (length - 1);
		x = (x>>1) | temp;
	}*/
	unsigned int temp=x&~(~0<<n);
	x=x>>n;
	temp=temp<<(length-n);
	x=x|temp;
	return x;
}