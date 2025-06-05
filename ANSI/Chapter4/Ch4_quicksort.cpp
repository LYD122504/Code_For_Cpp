#include<stdio.h>
void quicksort(int v[], int left, int right);
void swap(int v[], int i, int j);
int main()
{
    int v[10];
    printf("请输入10个数字用于排序");
    for (int i = 0; i < 10; i++)
    {
        int temp;
        scanf("%d", &temp);
        v[i] = temp;
    }
    quicksort(v, 0, 9);
    printf("排序结果为:");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}
//quicksort: sort v[left]...v[right] into increasing order
void quicksort(int v[], int left, int right)
{
    int i, last;
    if (left >= right)return;
    //将中间值作为基准将其移动到最左边
    swap(v, left, (left + right) / 2);
    //设置一个flag用来记录比基准小的数的最后位置
    last = left;
    for (i = left + 1; i <= right; i++)
      //这里用++来保证我们整理的比基准小的数不会污染基准的值
        if (v[i] < v[left])
            swap(v, ++last, i);
    //此时结构应该是 基准 left-last比基准小的 last-right比基准大或等于基准
    //此时将基准换到last的位置，会使基准左侧全是小于基准，右侧是大于等于基准的
    swap(v, left, last);
    quicksort(v, left, last - 1);
    quicksort(v, last + 1, right);
}
//swap: interchange v[i] and v[j]
void swap(int v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
