#include<stdio.h>
int binsearch(int x,int v[],int n);
int main()
{
  int v[6]={0,2,4,6,8,10};
  int n=6;
  int x=3;
  int u=binsearch(x, v, n);
  printf("需要查找的元素为第 %d 位",u);
}
// binsearch: find x in v[0]<=v[1]<=...<=v[n-1]
int binsearch(int x,int v[],int n)
{
  int low,high,mid;

  low=0;
  high=n-1;
  while(low<=high)
    {
      mid=(low+high)/2;
      if(x<v[mid])
	high=mid-1;
      else if (x>v[mid])
	low=mid+1;
      else
	return mid;// found match
    }
  return -1;//no match
}
