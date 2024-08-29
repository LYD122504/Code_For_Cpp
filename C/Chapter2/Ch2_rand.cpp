#include<stdio.h>
unsigned long int next=1;
int rand(void);
void srand(unsigned int seed);
int main()
{
  unsigned int seed;
  printf("请输入一个大于0的随机种子\n");
  scanf("%u", &seed);
  srand(seed);
  printf("生成的随机数为 %d\n",rand());
  printf("生成的随机数为 %d\n",rand());
}
//rand: return pseudo-random integer on 0..32767
int rand(void)
{
  next=next*1103515245+12345;
  return (unsigned int) (next/65536)%32768;
}
// srand: set seed for rand()
void srand(unsigned int seed)
{
  next=seed;
}
