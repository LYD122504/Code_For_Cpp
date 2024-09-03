//计算器头文件,用于声明需要的函数
#define NUMBER '0'
// 缓冲区的输入操作
int getch();
void ungetch(int);
void ungets(char s[]);
int mod_getch();
void mod_ungetch(int);
//getop 输入字符串
int getop(char s[]);
int getline(char s[], int lim);
int mod_getop(char s[], char* line);
//栈操作
void push(double);
double pop();
double show_top();
void copy_top();
void swap_top();
void clean();
