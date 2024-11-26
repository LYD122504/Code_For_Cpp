#include<stdio.h>
void swap(int* a, int* b);
int main()
{
	int a, b;
	printf("请输入第一个数字:");
	scanf("%d", &a);
	printf("请输入第二个数字:");
	scanf("%d", &b);
	swap(&a, &b);
	printf("第一个数字: %d, 第二个数字: %d\n", a, b);
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}