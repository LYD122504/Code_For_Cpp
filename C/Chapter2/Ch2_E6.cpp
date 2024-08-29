#include<stdio.h>
#include<math.h>
unsigned setbits(unsigned x, int p, int n, unsigned y);
int main()
{
	unsigned x = 12331;
	int p = 11;
	int n = 3;
	unsigned y = 65535;
	unsigned z = setbits(x, p, n, y);
	printf("%u", z);
}
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	return ((y & ~(~0 << n)) << (p + 1 - n)) | (x & ~(( (int)pow(2,n) - 1) << (p + 1 - n)));
}