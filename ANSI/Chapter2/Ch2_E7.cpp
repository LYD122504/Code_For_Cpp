#include<stdio.h>
#include<math.h>
unsigned invert(unsigned x, int p, int n);
int main()
{
	unsigned x = 255;
	int p = 5;
	int n = 3;
	unsigned z = invert(x, p, n);
	printf("%u", z);
}
unsigned invert(unsigned x, int p, int n)
{
	unsigned temp = (x >> (p + 1 - n)) & ~(~0 << n);
	temp ^= (int) pow(2,n) - 1;
	return (temp << (p + 1 - n)) | (x & ~(((int)pow(2, n) - 1) << (p + 1 - n)));
}