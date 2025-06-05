#include <stdio.h>
#include <malloc.h>
#include<vld.h>
/*typedef struct Test {
  double size;
  char c[0];
} Test;
int main() {
  int sz = 100;
  struct Test *pt = (Test *)malloc(sizeof(Test) + sizeof(int) * sz);
  pt->size = sz;
  for (int i = 0; i < pt->size; i++)
    pt->c[i] = i + 1;
  for (int i = 0; i < pt->size; i++)
    printf("%d ", pt->c[i] = i + 1);
  printf("\n");
  printf("%lu",sizeof(Test));
  }*/
typedef struct Test {
  int size;
  int* pt;
} Test;
int main() {
  int sz = 100;
  struct Test *pt = (Test *)malloc(sizeof(Test));
  int *ptr=(int*) malloc(sizeof(int) * sz);
  pt->size = sz;
  pt->pt=ptr;
  for (int i = 0; i < pt->size; i++)
    pt->pt[i] = i + 1;
  for (int i = 0; i < pt->size; i++)
    printf("%d ", pt->pt[i] = i + 1);
  printf("\n");
  free(ptr);
  free(pt);
  printf("%lu",sizeof(int*));
  }
