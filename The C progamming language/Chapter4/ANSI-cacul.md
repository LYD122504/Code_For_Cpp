---
title: ANSI-Reverse Polish Calculator
date: 2024-12-30 22:41:46
tags:
    - Computer Science
    - C Language
categories: C Language
mathjax: true
---

## 逆波兰表达式计算器代码(Chapter4)


<a id="org3f3d92b"></a>

### 逆波兰表达式

我们使用最为频繁的计算表达式其实是中缀表达式, 也就是操作符在两个操作数之间. 这个的缺点在于, 加减乘除的优先级并不是简单的从左到右计算的, 而是存在一定的优先级. 因此如果我们想要得到想要的结果, 就必须使用括号来辅助我们的计算, 而括号的嵌套则会使计算的复杂度大幅增加. 所以, 我们引入逆波兰表达式, 也就是所谓的后缀表达式, 其特点在于将操作符直接置于操作数之后. 其具体的用法如, $(3-4)*5$ 的逆波兰表达式为 $3\ 4\ -\ 5\ *$; $3-4*5$ 的逆波兰表达式为 $3\ 4\ 5\ *\ -$. 逆波兰表达式的优点在于, 他不需要括号, 也不需要考虑优先级, 只需要按照顺序进行计算即可.

<!--more-->

<a id="org00a5db2"></a>

### 计算器的设计思路

我们基于前面提到的逆波兰表达式的思想, 我们发现这个流程其实是符合后进先出的原则, 因此我们采用栈的数据结构来实现这个计算器. 具体思路如下: 我们每次从输入缓冲区中读取一个字符, 如果是数字, 那么我们就将其压到栈里; 如果是操作符, 暂时我们只考虑二元操作符, 那么我们就从栈顶弹出两个数进行计算, 如果操作数不够, 就弹出异常报错, 最后我们将计算的结果重新压入栈中. 如果我们在此过程中读取到了结束符, 弹出栈顶元素后, 检查栈是否为空, 如果为空, 那么我们就得到了计算结果, 如果不为空, 那么我们就得到了异常报错.


<a id="org4ea7795"></a>

### 模块实现

我们将上述过程分成三个大模块和一个主函数, 分别是: getop, getch, stack. 


<a id="orgc9f8cf7"></a>

#### stack模块(栈操作模块)

栈从修改的角度来说, 只有两种操作, 一种是压栈(push), 另一个则是弹栈(pop). 我们在此用数组的形式来实现栈, 我们设置一个指标pos作为标注下一个空闲栈的位置. 显然我们的push和pop操作都需要操作栈空间和栈指标, 因此我们在定义栈和指标的时候, 我们需要将其定义为全局变量. 代码如下所示

```c++
#include<stdio.h>
#define MAXVAL 100// maximum depth of val stack
int sp = 0; // new free stack position
double val[MAXVAL]; // value stack
// pop: pop and return top value from stack
double pop()
{
  if (sp)
    return val[--sp];
  else
    {
      printf("ERROR: empty stack.\n");
      return 0.0;
    }
}
// push: push f onto value stack
void push(double v)
{
  if (sp < MAXVAL)
    val[sp++] = v;
  else
    printf("ERROR: stack full, can not push %g\n", v);
}
```

在这里, 其实我们可以进一步要求sp和val是静态的, 也就是只能在本文件中使用, 这样的话, 会使代码更加安全.


<a id="orgc676a68"></a>

#### getop模块(获取操作数/符模块)

这里我们需要考虑的是, 一个操作数可能是多位数, 也可能是小数; 至于负数, 我们可以用0-x的形式来表示. 其流程如下: 首先我们需要先跳过操作数/符之前的空格或制表符, 然后我们读取一个字符, 判断是不是数字, 如果不是数字部分,我们就将其返回; 如果是数字部分, 那我们将其收集起来并继续读取, 直到一个非数字的字符出现,在此我们又要判断是否是小数点, 如果是小数点, 也就是我们接下来读取小数部分; 反之则是已经读取结束. 值得注意的是, 我们在读取这些的过程经常会出现, 读取了一个字符, 以后发现不是我们想要的, 这时我们需要将其放回缓冲区(我们将会在后面的模块设置), 并不可以直接丢弃.

```c++
int getop(char s[])
{
  int i, c;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.')
    return c; /* not a number */
  i = 0;
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}
```

<a id="orgb9de190"></a>

#### getch模块(获取字符模块)

这个模块的作用是从输入缓冲区中读取一个字符, 并返回. 但是我们在这里需要考虑的是, 有时候我们读取了一个字符, 发现不是我们想要的, 那么我们就需要将其放回缓冲区, 以便下次读取.

```C++
#include<stdio.h>
#include<string.h>
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{	
  if (buf[bufp - 1] == EOF)
    printf("EOF!");
  return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
```

<a id="org9564f38"></a>

### 主函数

在主函数其实我们只需要不断调用getop函数, 并根据返回值的不同来进行不同的操作即可.

```c++
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "calc.h"
#define MAXOP 100
#define MAXLINE 1000 // length of a maximum line to be read
//reverse Polish calculator
int main()
{
    int type;
    double op2=0.0;
    char s[MAXOP];
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            v = atof(s);
            push(v);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2)
                push(pop() / op2);
            else
                printf("ERROR: zero divisior.\n");
            break;
        case '\n':
            op2 = pop();
            printf("\t%.8g\n", op2);
            break;
        default:
            printf("ERROR: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
```

这里注意的是, 我们的减法和除法是有顺序的, 也就是我们需要先存储下第一个操作数,等第二个操作数弹出, 再操作, 这样才能保证我们的计算是正确的.


<a id="org0165295"></a>

### 头文件

```c++
//计算器头文件,用于声明需要的函数
#define NUMBER '0'
// 缓冲区的输入操作
int getch();
void ungetch(int);
//getop 输入字符串
int getop(char s[]);
//栈操作
void push(double);
double pop();
```


<a id="org13a1856"></a>

### 多文件编译过程

C/C++ 程序执行流程其实是先将源文件编译成中间代码文件, 在windows下是.obj文件, 在linux下是.o文件, 然后再将这些文件链接成可执行文件. 举个例子, 我们如果对上面的代码编译,那么我们需要先对这些文件进行编译,也就是

```shell
gcc -c stack.c
gcc -c getch.c
gcc -c getop.c
gcc -c main.c
```

此时,我们会得到四个中间文件, 分别是stack.o, getch.o, getop.o, main.o. 然后我们再将这些文件链接成可执行文件

```shell
gcc -o calc stack.o getch.o getop.o main.o
```

但是很显然如此操作, 如果我们修改了一个文件, 我们就要重新走一遍这个流程, 这样的效率是很低的. 因此我们可以使用makefile来自动化这个过程. 我们先给出一个上面的makefile文件的版本

```makefile
#version1
#在这个makefile中，目标文件（target）包含：执行文件edit和中间目标文件（*.o），依赖文件（prerequisites）就是冒号后面的那些 .c 文件和 .h文件。每一个 .o 文件都有一组依赖文件，而这些 .o 文件又是执行文件 edit 的依赖文件。依赖关系的实质上就是说明了目标文件是由哪些文件生成的，换言之，目标文件是哪些文件更新的
#在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，一定要以一个tab键作为开头。make并不管命令是怎么工作的，他只管执行所定义的命令。make会比较targets文件和prerequisites文件的修改日期，如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。
#执行命令一定是以一个tab键作为开头的
maincc:main.o getch.o getop.o stack.o
g++ main.o getch.o getop.o stack.o -o maincc    #用g++把中间文件链接编译成可执行文件,并且用-o将其命名为maincc
#这一步是告知计算机main.o文件的生成需要用到main.cpp文件
main.o:main.cpp
g++ -c main.cpp    #用g++来将cpp文件编译成.o文件
getop.o:getop.cpp
g++ -c getop.cpp
stack.o:stack.cpp
g++ -c stack.cpp
getch.o:getch.cpp
g++ -c getch.cpp
clean: 
rm -f main.o getch.o getop.o stack.o
```

如果我们新增了一个文件, 那么我们需要在这个makefile文件里, 两处地方添加文件依赖, 可能会出现漏加的情况,因此我们引入一个变量来避免这个问题.

```makefile
#version 2
#由于版本1中,如果我们需要增加一个新的.o文件就需要手动修改三个地方,这在多任务下可能出现遗忘,因此引入makefile的变量即可
objects=main.o getch.o getop.o stack.o
maincc: $(objects)
g++ $(objects) -o maincc
main.o:main.cpp
g++ -c main.cpp    #用g++来将cpp文件编译成.o文件
getop.o:getop.cpp
g++ -c getop.cpp
stack.o:stack.cpp
g++ -c stack.cpp
getch.o:getch.cpp
g++ -c getch.cpp
.PHONY : clean
clean:
-rm maincc  *.o
```

这样, 我们只需要修改objects变量和下面的编译指令即可. 不过在此之前, 我们先解释一下最后的部分, 最后的部分作用其实就是删除中间文件和执行文件, 这可以保证我们文件干净. 这个-rm指的是如果有些文件不存在, 那就别管他继续往后删. .PHONY指的是clean是一个伪目标, 也就是不是一个文件.

事实上, 我们还可以进一步简化这个makefile文件,利用makefile的自动推导规则, 也就是makefile会自动推导出.o文件是由.cpp文件生成的, 因此我们可以将上面的makefile文件简化为

```makefile
#事实上,我们还可以对上面的版本进行简化,GNU下的make命令可以自动推导文件以及文件依赖关系后面的命令，于是我们就没必要去在每一个[.o]文件后都写上类似的命令，因为，我们的make会自动识别，并自己推导命令。
objects=main.o getch.o getop.o stack.o
maincc: $(objects)
    g++ $(objects) -o maincc
main.o:main.cpp
getop.o:getop.cpp
stack.o:stack.cpp
getch.o:getch.cpp
.PHONY clean: 
    rm -f  *.o
```

