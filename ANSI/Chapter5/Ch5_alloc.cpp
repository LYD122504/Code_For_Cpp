#include<stdio.h>
char* alloc(int n);
void afree(char* p);
int main()
{
  int n1,n2;
  char* p1,*p2;
  printf("请输入申请的空间大小:");
  scanf("%d%*c",&n1);
  p1=alloc(n1);
  printf("申请到的空间的初始位置地址为 %p,终止位置地址为 %p.\n",p1,p1+n1-1);
  printf("请输入给定的字符串:");
  scanf("%[^\n]%*c",p1);
  printf("已经存储的字符串为 %s.\n",p1);
  printf("请输入申请的空间大小:");
  scanf("%d%*c",&n2);
  p2=alloc(n2);
  printf("申请到的空间的初始位置地址为 %p,终止位置地址为 %p.\n",p2,p2+n2-1);
  printf("请输入给定的字符串:");
  scanf("%[^\n]%*c",p2);
  printf("已经存储的字符串为 %s.\n",p2);
}
#define ALLOCSIZE 10000 // size of available space
static char allocbuf[ALLOCSIZE]; //storage for alloc
static char* allocp=allocbuf; // next free position
// alloc return pointer to n characters
char* alloc(int n)
{
  if (allocbuf+ALLOCSIZE-allocp>=n)// Determine whether there is enough space
    {
      allocp+=n;// find the next free position
      return allocp-n;
    }
  else return 0;// not enough space
}
//afree frees storage pointed to by p
void afree(char*p)
{
  if(p>=allocbuf&&p<allocbuf+ALLOCSIZE)
    allocp=p;
}
