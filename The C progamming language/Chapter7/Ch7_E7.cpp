#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
void filecopy(FILE* fp,char *fname,char*pattern,int except,int number);
int main(int argc,char *argv[]) {
  //读取命令行参数
  int c;
  int except, number;
  FILE *fp;
  char pattern[MAXLINE];
  except=number=0;
  while (--argc && (*++argv)[0] == '-') {
	/* 这个部分的注释解释(*++argv)[0]
	   argv:从形参来看是一个指针数组的形式,但是实际上argv是一个双重指针的实现,也就是argv允许赋值运算
	   ++argv:这相当于让argv做一个自增运算,即argv=argv+1,同时返回自增结束的argv的值.
	   *++argv:这相当于在++argv的基础上,做了一个解引用操作,即取出了argv+1指向的地址对应的元素,值得注意的是*++argv仍然是一个字符指针
	   (*++argv)[0]:表示取出字符指针指向的第一个字符
	*/
	while (c = *++argv[0]) {
	  /* 这个部分的注释解释*++argv[0]
		 argv[0]:其实这样写的太过迷惑性,可以认为他就是*argv,也就是取出argv指向的字符指针
		 ++argv[0]:将上面所说的这个指针自增后并返回自增的结果
		 *++argv[0]:取出字符,这里其实就是先将argv指向的字符指针取出自加以后,这时候这个字符指针已经向后移动了,取出对应的字符即可
		 */
      switch (c) {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        printf("find: illegal option %c\n", c);
        argc = 0;
		break;
      }
    }
  }
  // -nx之后紧接着pattern
  if (argc >= 1)
    strcpy(pattern, *argv);
  else
	{
	  printf("Usage:find [-x] [-n] pattern[file...]\n");
	  exit(1);
	}
  if (argc == 1)
    filecopy(stdin,(char* )"",pattern,except,number);
  else
    while (--argc) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
		fprintf(stderr,"find:can't open %s\n",*argv);
		exit(2);
      }
	  else {
        filecopy(fp,*argv,pattern,except,number);
        fclose(fp);
	  }
    }
	  
}
void filecopy(FILE *fp, char *fname, char *pattern, int except, int number) {
  char line[MAXLINE];
  long lineno = 0;
  while (fgets(line, MAXLINE, fp) != NULL) {
    ++lineno;
    if ((strstr(line, pattern) != NULL) != except) {
      if (*fname)
        printf("%s-", fname);
      if (number)
        printf("%ld:", lineno);
	  printf("%s",line);
    }
  }
}
