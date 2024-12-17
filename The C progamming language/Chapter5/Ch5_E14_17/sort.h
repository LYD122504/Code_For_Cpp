#pragma once
#define MAXLINES 5000
#define MAXLEN 100

// input and output
int readline(char* lineptr[], int nlines);
void writeline(char* lineptr[], int nlines);
int getline(char* s, int nchars);
// sort program
//void qsort(char* lineptr[], int left, int right);
//函数指针版本
void qsort(char* lineptr[], int left, int right, int (*comp)(void*, void*));
void swap(char* v[], int i, int j);
int strcmp(char* s, char* t);
int fieldcmp(char* s, char* t);
int numcmp(char* s, char* t);
void strcpy(char* s, char* t);
// malloc and free
char* alloc(int n);
void afree(char* p);