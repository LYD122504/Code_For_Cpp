#version1

#在这个makefile中，目标文件（target）包含：执行文件edit和中间目标文件（*.o），依赖文件（prerequisites）就是冒号后面的那些 .c 文件和 .h文件。每一个 .o 文件都有一组依赖文件，而这些 .o 文件又是执行文件 edit 的依赖文件。依赖关系的实质上就是说明了目标文件是由哪些文件生成的，换言之，目标文件是哪些文件更新的

#在定义好依赖关系后，后续的那一行定义了如何生成目标文件的操作系统命令，一定要以一个tab键作为开头。make并不管命令是怎么工作的，他只管执行所定义的命令。make会比较targets文件和prerequisites文件的修改日期，如果prerequisites文件的日期要比targets文件的日期要新，或者target不存在的话，那么，make就会执行后续定义的命令。

#执行命令一定是以一个tab键作为开头的
#maincc:main.o getch.o getop.o stack.o
	#g++ main.o getch.o getop.o stack.o -o maincc    #用g++把中间文件链接编译成可执行文件,并且用-o将其命名为maincc
#这一步是告知计算机main.o文件的生成需要用到main.cpp文件
#main.o:main.cpp
	#g++ -c main.cpp    #用g++来将cpp文件编译成.o文件
#getop.o:getop.cpp
	#g++ -c getop.cpp
#stack.o:stack.cpp
	#g++ -c stack.cpp
#getch.o:getch.cpp
	#g++ -c getch.cpp
#.PHONY clean: 
	#rm -f  *.o
	
#version 2
#由于版本1中,如果我们需要增加一个新的.o文件就需要手动修改三个地方,这在多任务下可能出现遗忘,因此引入makefile的变量即可
#objects=main.o getch.o getop.o stack.o
#maincc: $(objects)
	#g++ $(objects) -o maincc
#main.o:main.cpp
	#g++ -c main.cpp    #用g++来将cpp文件编译成.o文件
#getop.o:getop.cpp
	#g++ -c getop.cpp
#stack.o:stack.cpp
	#g++ -c stack.cpp
#getch.o:getch.cpp
	#g++ -c getch.cpp
#.PHONY clean: 
	#rm -f  *.o
	
#version3
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
