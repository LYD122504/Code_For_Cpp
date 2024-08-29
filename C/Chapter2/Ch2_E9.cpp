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
int bitcount(unsigned x)
{
	int b = 0;
	for (; x != 0; x &= (x - 1))
		b++;
	return b;
}