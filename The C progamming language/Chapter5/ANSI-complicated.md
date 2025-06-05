---
title: ANSI-complicated
date: 2025-01-21 00:08:33
tags:
    - Computer Science
    - C Language
categories: C Language
mathjax: true
---

## 复杂声明(Chapter 5)

由于C语言设计指针的声明需要嵌套大量的括号且并不能简单的从左到右阅读, 因此给定一个复杂的声明, 我们极难快速分析出其含义. 在此, 我们需要写一个程序用来实现将C语言的复杂声明转换为文本, 同理还有一个将文本转为声明的程序.

<!--more-->


### 设计思路

我们将声明符分为两类,一类是dcl,其主要是前面会带有可选的\*号的direct-dcl,其主要用来处理指针类型;第二类则是direct-dcl,其主要是如name,(dcl),direct-dcl(),direct-dcl[]的类型.很显然无论声明是什么形式,我们都可以将其视作dcl的形式,因此我们只需要设计两个函数dcl和dirdcl即可.

在设计dcl和dirdcl函数之前,我们需要先设计一个用来读取输入类型的函数gettoken,其作用不仅仅是读取下一个输入流的输入,更是识别下一个输入的符号类型,并返回其类型.大体我们可以将记号类型分为如下几种:NAME,PARENS,可能包含数字的BRACKETS,以及其他任意单个字符.这里我们逐一分析输入情况,首先我们需要跳过初始输入的空格和制表符;其次如果我们接收到左括号,那么如果紧接着右括号,那么我们就返回PARENS,否则代表了左括号后面还有内容,因此我们需要将已读取的字符重新压入缓冲区,并返回左括号.如果我们接受到的是左方括号,那么其后面只可能跟进数字,无所谓内部内容,我们只需要通过循环找到右方括号即可,并返回BRACKETS;如果我们接收到的是字母,那么我们是在读取一个名称,为了简便起见,我们忽略变量名中出现下划线的情况,因此我们只需要判断后续字符是否是字母或者数字,直到遇到第一个非数字或字母的字符,我们将其压回缓冲区,并返回NAME;最后,如果我们接收到的是其他字符,那么我们直接返回该字符.

在设计完输入类型读取函数之后,我们开始设计dcl函数,首先由我们前面的dcl类型的声明定义可知,我们的dcl函数只去处理指针类型的声明,因此我们需要统计\*的个数并且在出现第一个非\*字符时表明我们进入了dirdcl类型之中;值得注意的是,我们在函数栈弹出回到dcl过程中的时候,因为一个\*就代表了一个指针形式,因此我们需要循环添加pointer to语句.

对于dirdcl函数而言,如果输入标签为左括号,那么后续跟进的一定是dcl,值得注意的是,这样返回到dirdcl函数中的时候,我们需要进一步判断是否出现右括号,如果没有,则报错;如果输入标签为NAME,那么我们只需要输出这个名字即可;如果不是这两个形式的开头那么就需要报错.其次我们就要考虑后缀括号或方括号的情况:如果是括号,那么表示这是一个函数,我们只需要输出函数的形式即可;如果是方括号,那么表示这是一个数组,我们只需要输出数组的形式即可.


### 代码实现

main函数

```c++
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define BUFSIZE 100
#define MAXTOKEN 100
enum {NAME,PARENS,BRACKETS};
char buf[BUFSIZE];//缓冲区
int bufp = 0;//缓冲区空闲的后一位
int tokentype;//最后一个字符的类型: 类型名NAME，括号PARENS，方括号BRACKETS
char token[MAXTOKEN];// 最后一个token的字符串
char name[MAXTOKEN];// 声明的变量名
char datatype[MAXTOKEN]; // 声明的类型名
char out[1000];

int getch(void);
void ungetch(int c);
int gettoken(void);//用来读取下一个字符
void dcl(void);
void dirdcl(void);

int main()
{
    //读取输入
    while (gettoken() != EOF)
    {
        //第一个输入一定是类型名
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
```

getch and ungetch(读取缓冲区与压入缓冲区)

```c++
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters.\n");
    else
        buf[bufp++] = c;
}
```

dcl和dirdcl函数

```c++
//dcl的用处是处理指针符号
void dcl(void)
{
    int np;
    for (np = 0; gettoken() == '*'; np++);
    dirdcl();
    while (np--)
        strcat(out, " pointer to");
}
//dirdcl处理的是类型名dirdcl()/dirdcl[]，圆括号(dcl)
void dirdcl(void)
{
    int type;

    if (tokentype == '(')
    {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    }
    else if (tokentype == NAME)//变量名
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
```

gettoken函数

```c++
int gettoken(void)
{
    int c;
    char* p = token;
    //处理空格
    while ((c = getch()) == ' ' || c == '\t');
    //处理括号	
    if (c == '(')
    {
        //完整括号
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        //括号里有内容
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    //处理方括号
    else if (c == '[')
    {
        for (; (*p++ = c) != ']'; c = getch());
        *p = '\0';
        return tokentype = BRACKETS;
    }
    //处理类型名和变量名
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        ungetch(c);
        *p = '\0';
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}
```

### Exercise 5-18

Make dcl recover from input errors.

这里给的解决办法就是如果出现问题,我们就跳转到行末,然后设置一个标志位,再下一次输入修正错误.因此我们只需要补一个错误设置函数即可.

```c++
void set_false(void)
{
    int c;
    if (tokentype != '\n')
        while ((c = getch()) != '\n')
            ;
    tokentype = '\n';
    flag = 1;
}
```
