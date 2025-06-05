#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

union u_tag {
	int ival;
	float fval;
	char* sval;
};
int main()
{
	char tag[20];
	printf("The size of int is %d.\n", sizeof(int));
	printf("The size of float is %d.\n", sizeof(float));
	printf("The size of char* is %d.\n", sizeof(char*));
	printf("The size of union is %d.\n", sizeof(u_tag));
	u_tag utag;
	//remark:这里实际上是可以用char*指针的形式来存储,但是由于char*一开始未初始化的时候分配的空间可能比较危险,故不推荐使用
	//建议使用char数组更为安全
	scanf("%s", tag);
	if (strcmp(tag, "INT") == 0)
	{
		scanf("%d", &utag.ival);
		printf("The type is %s and its value is %d.\n", tag, utag.ival);
	}
	else if (strcmp(tag, "FLOAT") == 0)
	{
		scanf("%f", &utag.fval);
		printf("The type is %s and its value is %f.\n", tag, utag.fval);
	}
	else if (strcmp(tag, "CHAR*") == 0)
	{
		char str[100];
		scanf("%f", str);
		utag.sval = str;
		printf("The type is %s and its value is %s.\n", tag, utag.sval);
	}
	else
		printf("The type is wrong.\n");
}