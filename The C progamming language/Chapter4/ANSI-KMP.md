---
title: ANSI-KMP算法
date: 2024-08-28 19:59:05
tags:
    - Computer Science
    - C Language
categories: C Language
mathjax: true
---

在C语言程序设计这本书的第四章中提到了strindex 函数的编写; 其针对的问题是如何在主串(文本串)中找到某种类型的子串, 也就是我们常说的字符串匹配问题. 显然这个方法是存在朴素求解算法的, 在此我们将介绍除朴素求解算法以外的, 另一种优化的匹配算法, 即 KMP 算法和 KMP 算法的两种不同的实现思路.

<!--more-->

## 暴力搜索法 (Brute Force)

### 算法思想

对于文本串 T 和模式串 P, 从文本串的第一个字符与模式串的第一个字符开始匹配; 如果相等, 那么比较位置同时后移, 比较第二个字符是否匹配, 以此类推; 直到出现模式串结束, 那么输出文本串的位置; 或者出现有一个不匹配的字符, 那么将文本串回退到最早比较的下一个字符, 模式串回退到开始, 重新循环.

### 算法实现

```c
int strindex(char* text,char* pattern)
{
  int i,j,k;
  for(i=0;s[i]!='\0';i++)//文本串的循环
    {
      for(k=i,j=0;pattern[j]!='\0'&&pattern[j]==text[k];j++,k++)
          //模式串的循环
	;
    if(j>0&&pattern[j]=='\0')//判断是否为真正匹配结束
      return i;
    }
  return -1;
}
```

### 算法分析

我们假设文本串的长度为 $n$, 模式串的长度为 $m$. 

最坏的情况是类似于文本串为AAAAAAAB, 模式串为AAAB,这样的话, 需要匹配$(n-m+1)m$ 次, 时间复杂度为 $O(nm)$.

最好的情况则是第一次匹配就成功, 那么时间复杂度就是 $O(m)$.

如果我们考虑每种情况以等概率的情况出现, 我们可知 BF 算法的平均时间复杂度为 $O(nm)$.

## KMP 算法

我们在上面发现对于文本串为AAAAAAAB, 模式串为AAAB的匹配, 每次都是在最后一个字母匹配出错, 然后就要将模式串和文本串同时回退, 重新比较; 这一步会消耗大量的时间, 并且完全没有利用到前面匹配的结果; 因此KMP算法的提出就是为了解决上面提到的问题: 其利用了匹配失败以前的匹配成功的结果, 从而将时间复杂度降到了 $O(n+m)$.

### KMP 算法的基本思想

其核心思想就是当出现不匹配的情况, 利用已知匹配的结果避免回退文本串的指针并且尽可能少的回退模式串的指针.

例如, 如果我们匹配到第 j 个字符串出现了字符不匹配现象, 那么我们已知的是 P[0:j-1]=T[i:i+j-1], BF 算法对这个的处理是直接回退文本指针和模式指针, 并不利用这一良好性质. 而 KMP 算法则是需要寻找 P[0:j-1] 的最长相等前后缀,因为已知 P[0:j-1]=T[i:i+j-1]; 假设 P[0:j-1] 的最长相等前后缀长度为 k,那么你就可以通过一个连等式快速得到需要回退的位置, 即 P[0:k-1]=P[j-k:j-1]=T[j-k:j-1]; 如此可知实际上, 即使我们用暴力搜索重新去计算, 只不过是不断地失败, 直到达到上面所说的情况而已.

### 基于 PMT 的 KMP 算法

上面介绍了 KMP 算法的基本思想, 接下来我们就用不同的实现思路去实现 KMP 算法的思想. 首先我们引入 PMT (Partial Match Table, 部分匹配表) 的概念, 其实这个表就是将要介绍的前缀表.

#### 前缀表的定义

前缀表在 KMP 算法中的作用是用来控制模式指针的回退, 其记录的是字符串的最长相等前后缀的长度, 其用于寻找当出现模式串与文本串不匹配的时候, 模式串应该从哪里开始重新匹配.

例如对于文本串 T=aabaacaabaaf, 模式串为 P=aabaaf; 在第一次字符串匹配时, P[5]和T[5]不匹配了, 如果用 BF 算法, 那么我们下一次匹配就是 P[0] 和 T[1] 的比较; 但显然我们通过朴素的思考, 因为 P[0:4]=aabaa 的最长相同前后缀为 aa, 所以利用 KMP 算法的下一次匹配实际上是考虑 P[2] 和 T[5] 的匹配, 显然如此, 匹配速度有很大的提升.

前缀表是记录下标 i 之前 (包括 i) 的字符串中的最长相同前后缀的长度.

对于一个字符串的前缀指的是包含首字符, 但不包含尾字符的字符串; 例如 aabaaf 的前缀集合为 {a,aa,aab,aaba,aabaa}

对于一个字符串的后缀指的是包含尾字符, 但不包含首字符的字符串; 例如 aabaaf的后缀集合为 {f,af,aaf,baaf,abaaf}

#### 前缀表的计算思路及代码实现

1. 引入两个指针 i 和 j; j 用来指示前缀的末尾, i 用来指示后缀的末尾; 换言之, i 会从 0 开始遍历模式串的每一个下标, j 则是用于记录 P[0:i-1] 的最长相等前后缀的长度.
2. 如果模式串的第 i 位和模式串的第 j 位相等, 那么 j++, i++即可
3. 如果模式串的第 i 位和模式串的第 j 位不相等, 那么就要做一个持续回退; 因为已知 P[j]!=P[i], 但是 P[0:j-1]=P[i-j:i-1]; 那么我们可以用 j=pmt[j-1] 来回退到 P[0:j-1] 的最长相等前后缀的后一位; 这一步的依据是首先 P[0:j-1]=P[i-j:i-1], 并且我们假设 k 为 P[0:j-1] 的最长相等前后缀长度, 那么 P[0:k-1]=P[j-k:j-1]=P[i-k:i-1], 如此就可以去比较 P[k] 和 P[i].
4. 更新 pmt 数组

代码实现如下:

```c
void generate_PMT(const string &pattern,int* pmt)
{
    int j=0;
    pmt[0]=0;
    for(int i=1;i<pattern.size();i++)
    {
        while(j>0&&pattern[i]!=pattern[j])
            j=pmt[j-1];
        if (pattern[i]==pattern[j])
            j++;
        pmt[i]=j;
    }
}
```

利用前缀表进行 KMP 算法匹配思路

1. 设置两个指针 i 和 j; i 用来控制在文本串的移动; j 用来控制在模式串的移动
2. 如果匹配没出错, 那么返回匹配的起点即可
3. 如果匹配出错了, 那么分情况讨论,如果 j=0, 即模式串的第一个字符就与其不匹配, 那么就需要将文本串向后移动一位; 如果 j 不为0, 那么就用 j=pmt[j-1] 去更新匹配成功部分的最长相等前后缀.
4. 输出结果

#### 利用前缀表进行 KMP 算法代码实现

```c++
void generate_PMT(const string &pattern,int* pmt)
{
    int j=0;
    pmt[0]=0;
    for(int i=1;i<pattern.size();i++)
    {
        while(j>0&&pattern[i]!=pattern[j])
            j=pmt[j-1];
        if (pattern[i]==pattern[j])
            j++;
        pmt[i]=j;
    }
}
int strindex(string text,string pattern)
{
    int j=0;
  	if (text.size()==0)
        return -1;
    if (pattern.size()==0)
        return 0;
    vector<int> pmt(pattern.size());
    generate_PMT(pattern,&pmt[0]);//&取地址
    for(int i=0;i<text.size();i++)
    {
        while(j>0&&text[i]!=pattern[j])
            j=pmt[j-1];
        if(text[i]==pattern[j])
            j++;
        if(j==pattern.size())
            return (i-pattern.size()+1);
    }
    return -1;
}
```



#### 用 next 数组实现 KMP 算法

我们在此额外介绍前缀表的另一种表示形式, 也就是 next 数组, 在市面上很多算法书更多采用这种. 我们只介绍其中一种 next 数组生成方法, 也就是将前缀表整体右移以后, 在第一个位置补上 -1. 我们给出代码实现

```c++
void generate_NEXT(const string& pattern, int* next)
{
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < pattern.size(); i++)
    {
        while(j>=0&&pattern[i-1]!=pattern[j])
			j=next[j];
        if (j == -1 || pattern[i-1] == pattern[j])
            next[i] = ++j;
    }
}
int strindex(string text,string pattern)
{
    int j=0;
    if (text.size()==0)
        return -1;
    if (pattern.size()==0)
        return 0;
    vector<int> next(pattern.size());
    generate_NEXT(pattern,&next[0]);//&取地址
    for(int i=0;i<text.size();i++)
    {
        while(j>0&&text[i]!=pattern[j])
            j=next[j];
        if(j==-1||text[i]==pattern[j])
            j++;
        if(j==pattern.size())
            return (i-pattern.size()+1);
    }
    return -1;
}
```

### 基于 DFA 的 KMP 算法

#### DFA 的定义

自动机分为两类: DFA (确定性有限状态自动机) 和 NFA (非确定性有限状态自动机), 二者均可用于字符串匹配问题, 我们在此仅使用 DFA 来完成 KMP 算法. 而 NFA 主要用于正则表达式的匹配问题.

![微信图片_20240829160304](https://cdn.jsdelivr.net/gh/LYD122504/picx-images-hosting@master/微信图片_20240829160304.6png3qwz50.png)

由上图知, DFA 由状态 (带数字的圆圈) 和转换 (带模式串字母的箭头) 组成. 从上图知, 由于模式串为 ABABAC 六个字符, 因此 DFA 一共由七个状态, 其中状态 0 表示起始状态, 也就是未开始匹配的状态, 模式 6 为匹配成功的状态. 值得注意的是, 构建的 DFA 是基于模式串进行的, 文本串是一系列输入该 DFA 的参数; 从某种角度来说, 这与我们前面提到的 next 数组类似, 实际上这两个只是不同维度的同一内容而已.

进一步, 我们给出图中涉及的一些专业术语, 在字符串匹配问题上, 每个状态都表示模式串中各个字符串的索引值, 该图中给出了在每个状态下输入不同字符的状态的转换操作, 但实际上这些转换中只有 0-1-2-3-4-5-6 这一条是匹配转换(其实就是从第 i 个状态转换到第 i+1 个状态), 其余的转换操作都需要回退指针, 称之为非匹配转换.

#### 构建 DFA 的思路与算法实现

在计算机内部, 我们用二维数组 DFA[char][state] 来表示上面介绍的 DFA, 其中 DFA[i][j] 具体含义是在状态 j 的情况下输入字符 i 之后, 状态转换的结果.

从构建DFA的流程中, 我们知道 DFA 的状态转换只有两种类型: 匹配转换或者非匹配转换.对此分类讨论即可得到构建 DFA 的算法

如果状态转换是匹配转换, 也就是在第 j 个状态下输入的字符是 pattern[j], 那么匹配成功, 我们可以转换到第 j+1 个状态, DFA[pattern[j]][j]=j+1;

假如状态转换是非匹配转换, 也就是在第 j 个状态下输入的字符并不是 pattern[j]. 为了后续讨论简便, 我们用 i 来表示输入的文本串字符位置, 但是 text[i] 不等于 pattern[j]. 此时, 因为出现了匹配失败的情况, 我们需要回退状态, 但是我们尽量要避免和暴力算法一样直接回退到开始, 而是尽可能少的回退, 并且不排除任何可能情况, 这就是 KMP 算法本身的思想. 虽然我们在第 j 个状态下匹配失败, 但是我们已知 Pattern[0~j-1] 和 text[i-j~i-1] 已经完成了匹配. 所以无论如何从 text[i-j] 开始去寻找模式串已经是不可能成立的了, 所以此时我们就可以从 text[i-j+1]开始分析, 如果我们输入的新字符串是 text[i-j+1~i-1], 那么会出现在什么状态? 由于这个新字符串依赖的不仅仅是文本串的内容, 实际上由于 Pattern[0~j-1]=text[i-j~i-1], 我们可以认为输入的新字符串实际上是 Pattern[1~j-1]. 所以我们就得到了一系列等价表达, 即如果在第 j 个状态下输入的 text[i] 出现了非匹配转换, 其最终状态等价于输入text[i-j+1~i-1]以后再输入 text[i] 的状态,等价于输入 Pattern[1~j-1] 以后再输入 text[i] 的状态. 

此时会发现如果我们要知道第 j 个状态下的非匹配转换结果, 其实我们只需要知道 输入 Pattern[1~j-1] 之后的状态; 由于我们的 DFA 构造是递推的, 所以这个状态的转换结果是已经构造了的, 我们可以直接得到这个结果, 换言之其实是一个 DP 过程. 为了讲解方便, 我们引入一个重启状态的概念, 重启状态就是如果我们在第 j 个状态下出现了非匹配转换, 那么由我们前面的讨论得知, 输入 Pattern[1~j-1] 得到的状态就是第 j 个状态的重启状态, 第 j 个状态的非匹配转换和重启状态的对应字符转换状态一致. 

我们给出如下的例子来解释重启状态, 在上面的 DFA 的图中, 如果我们用 ABABAA 来输入这个 DFA 中, 在状态 5 中, 最后输入的字符是 A, 与 C 不匹配, 那么我们就需要去找这个状态的重启装态, 我们已知 Pattern[0~4]=ABABA, 寻找重启状态的话, 我们就需要输入 Pattern[1~4]=BABA, 通过查图, 我们可以发现状态 5 的非匹配转换和状态 3 的一致. 

为了解释方便, 我们用重启状态数组来加以解释, 虽然我们在代码中是以数的形式存在, 但这并不影响. X[j+1] 表示输入 Pattern[1~j] 之后再输入 Pattern[j+1] 得到的结果, 但是我们知道输入 Pattern[1~j] 得到的状态其实是 X[j], 所以我们要求的 X[j+1] 实际上是在状态 X[j] 的基础上输入 Pattern[j+1] 的状态, 也就是 X[j+1]=DFA[Pattern[j]][X[j]]. 我们初始化 X[0]=0.

下面给出构建 DFA 的代码,

```c++
void generate_DFA(const string& pattern, vector<vector<int>> &DFA)
{
    DFA[pattern[0]][0] = 1;
    int X;
    for (int j = 1, X = 0; j < pattern.size(); j++)
    {
        for (int i = 0; i < 256; i++)// 256是asc码的长度,需要将字符串内出现的所有可能字符都列入
            DFA[i][j] = DFA[i][X];
        DFA[pattern[j]][j] = j + 1;
        X = DFA[pattern[j]][X];
    }
}
```

其实, 在 DFA 中寻找重启状态, 我们用的是 Pattern[1~j-1] 重新输入, 这个其实就是我们在 PMT 中寻找最长相等前后缀的过程, 只是 DFA 将其可视化了而已, 或者说, 我们在前面构造的重启状态数组实际上就是 PMT. 因此这两个办法理论上没有任何区别, 不过 DFA 在空间存储方面消耗更大, 他是一个二维数组.

#### 用 DFA 实现 KMP 的算法实现

如果我们已经构造了 DFA 数组, 我们只需要存储对应状态和依次输入文本串到 DFA 即可. 值得注意的是, 循环结束的原因是

1. 达到匹配成功状态, 返回文本串匹配成功起点
2. 文本串达到末尾, 也就是匹配失败, 返回 -1

```c++
void generate_DFA(const string& pattern, vector<vector<int>> &DFA)
{
    DFA[pattern[0]][0] = 1;
    int X;
    for (int j = 1, X = 0; j < pattern.size(); j++)
    {
        for (int i = 0; i < 256; i++)
            DFA[i][j] = DFA[i][X];
        DFA[pattern[j]][j] = j + 1;
        X = DFA[pattern[j]][X];
    }
}
int strindex(string text, string pattern)
{
    const int R = 256;
    vector<vector<int>> DFA(R, vector<int>(pattern.size(), 0));
    generate_DFA(pattern, DFA);
    int i, j;
    for (i = 0, j = 0; i < text.size() && j < pattern.size(); i++)
    {
        j = DFA[text[i]][j];
    }
    if (j == pattern.size())
        return i - pattern.size();
    else return -1;
}
```

###  KMP 算法分析

如果模式串长度为 $m$, 文本串长度为 $n$.

空间复杂度显然是 $O(m)$

对于时间复杂度分析, 我们只考虑 PMT 的情况, DFA 完全类似. 由于 PMT 需要求解 PMT 数组/Next 数组和 KMP 搜索两部分代码, 所以我们逐步分析.

1. 求解 PMT 数组/ Next 数组; 外层的 for 循环需要迭代 $m-1$ 次, 但是里面嵌套了一个 while 循环, 如果我们试图直接寻找 while 的循环次数, 虽然可以得到结果, 但是显然不太现实. 我们利用 j 的值的变化来近似分析时间复杂度. j 的变化只有两种情况, 要么加一, 要么 j=pmt[j-1] 减少. 但是减少的程度其实依赖于 j++ 的程度, 而 j++ 和 i++ 都是同时发生的, 所以最多发生 $m-1$ 次, 因此这一步的时间复杂度是 $O(m)$
2. 搜索: for 循环走的次数是 $n-1$, while 的回退其实总体来说最多只可能走 $n-m$ 因此一共复杂度 $O(n+m)$
