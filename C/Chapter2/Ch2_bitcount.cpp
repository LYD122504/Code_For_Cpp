#include<stdio.h>
int bitcount(unsigned x);
int main()
{

	unsigned x;
	printf("请输入一个无符号常数:");
	scanf_s("%u", &x);
	int num = bitcount(x);
	printf("输入的常数二进制中1的个数为%d", num);
}
// bitcount: count 1 bits in x
int bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}