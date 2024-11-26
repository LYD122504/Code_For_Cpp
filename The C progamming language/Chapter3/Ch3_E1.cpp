#include<stdio.h>
int binsearch_v2(int x,int* v,int n);
int main()
{
  int v[6]={0,1,2,3,4,5};
  int x=8;
  int n=6;
  int u=binsearch_v2(x, v, n);
  printf("需要查找的元素为第 %d 位",u+1);
}
int binsearch_v2(int x,int* v,int n)
{
  int low,high,mid;
  low=0;
  high=n-1;
  mid=(low+high)/2;
  for(mid=(low+high)/2;low<=high&&x!=v[mid];mid=(low+high)/2)
    {
      if(x>v[mid])
	low=mid+1;
      else
	high=mid-1;
    }
  if(low<=high)
    return mid;
  else return -1;
}
