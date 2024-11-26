#include<stdio.h>
void shellsort(int v[],int n);
int main()
{
  int v[10];
  printf("请输入10个数字用于排序");
  for(int i=0;i<10;i++)
  {
    int temp;
    scanf("%d",&temp);
    v[i]=temp;
  }
  shellsort(v, 10);
  printf("排序结果为:");
  for(int i=0;i<10;i++)
  {
    printf("%d ",v[i]);
  }
  printf("\n");
}
//shellsort: sort v[0]...v[n-1] into increasing order
void shellsort(int v[],int n)
{
  int gap,i,j,temp;
  for(gap=n/2;gap>0;gap/=2)
    {
      for(i=gap;i<n;i++)
	for(j=i-gap;j>=0&&v[j]>v[j+gap];j-=gap)
	  {
	    temp=v[j];
	    v[j]=v[j+gap];
	    v[j+gap]=temp;
	  }
    }
}
