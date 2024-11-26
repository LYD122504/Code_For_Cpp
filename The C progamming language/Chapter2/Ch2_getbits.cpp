#include<stdio.h>
unsigned getbits(unsigned x,int p,int n);
int main()
{
  unsigned x;
  int p,n;
  printf("请输入一个无符号整数\n");
  scanf("%u",&x);
  printf("请输入需要查找的位置和位数(位置>位数-1)\n");
  scanf("%d%d",&p,&n);
  unsigned result;
  result=getbits(x, p, n);
  printf("得到的数据串对应的十进制为 %u\n",result);
}
//getbits: get n bits from position p
unsigned getbits(unsigned x, int p,int n)
{
  return (x>>(p+1-n))&~(~0<<n);
  //x>>(p+1-n)表示将x的数据位向右移动p+1-n位,由于我们假设最右端的数据位的位置为0,那么我们可以知道这样移动会将第p+1-n位数据移到最右端,这也是我们希望得到的数据位的开始
  //~(~0<<n)从优先级角度分析知道~0是第一个运行的他会将0转换为1,然后<<n向左移n位,那么结果是10000(后接n个0),最后再做一次~得到,01(n个1)
  //这里要先对0取非是因为,我们后续做左移n位的操作实际上是生成了n+1个数据位,不然的话,我们后续对这个n+1个数据位取非会得到n+1个1组成的数据串,那么我们就会发现,去做位与的操作我们实际得到的是n+1位数据
  //值得注意的是这里用的是正数,负数的内部存储是补码形式较为复杂
}
