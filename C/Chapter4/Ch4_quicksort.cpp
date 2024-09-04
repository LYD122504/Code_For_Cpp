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
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
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