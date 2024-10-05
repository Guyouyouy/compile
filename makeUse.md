https://cloud.tencent.com/developer/article/2312815
```c
//hello.c
#include <stdio.h>
#include "head.h"

int main(int argc, char *argv[])
{
    int a = 10; int b = 5;

    printf("%d+%d=%d\n", a, b, add(a, b));
    printf("%d-%d=%d\n", a, b, sub(a, b));
    printf("%d/%d=%d\n", a, b, div(a, b));
    printf("%dx%d=%d\n", a, b, mul(a, b));

	return 0;
}

//add.c
int add(int a, int b)
{
	return a+b;
}
//sub.c
int sub(int a, int b)
{
	return a-b;
}
//mul.c
int mul(int a, int b)
{
	return a*b;
}
//div.c
int div(int a, int b)
{
	return a/b;
}
//head.h
#ifndef _HEAD_H_
#define _HEAD_H_

int add(int , int );
int sub(int , int );
int div(int , int );
int mul(int , int );

#endif
```

# V1

```makefile
a.out : hello.c add.c sub.c mul.c div.c
	gcc hello.c add.c sub.c mul.c div.c -o a.out -I ./
```

# V2

```makefile
a.out : hello.o add.o sub.o mul.o div.o
	gcc hello.o add.o sub.o mul.o div.o -o a.out 

hello.o : hello.c
	gcc -c hello.c -o hello.o -I ./

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o

mul.o : mul.c
	gcc -c mul.c -o mul.o

div.o : div.c
	gcc -c div.c -o div.o
```

# v3

```makefile
hello.o : hello.c
	gcc -c hello.c -o hello.o -I ./

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o

mul.o : mul.c
	gcc -c mul.c -o mul.o

div.o : div.c
	gcc -c div.c -o div.o

a.out : hello.o add.o sub.o mul.o div.o
	gcc hello.o add.o sub.o mul.o div.o -o a.out 
```

# v4

ALL：指定 makefile 的终极目标。

```makefile
ALL : a.out

hello.o : hello.c
	gcc -c hello.c -o hello.o -I ./

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o

mul.o : mul.c
	gcc -c mul.c -o mul.o

div.o : div.c
	gcc -c div.c -o div.o

a.out : hello.o add.o sub.o mul.o div.o
	gcc hello.o add.o sub.o mul.o div.o -o a.out
```

=======================================================================================

### 两个函数和 clean

找到当前目录下所有后缀为 .c 的文件，赋值给 src

```makefile
src = $(wildcard ./*.c) # 匹配当前工作目录下的所有.c 文件。将文件名组成列表，赋值给变量 src。 src = add.c sub.c mul.c div1.c
```

把 src 变量所有后缀为 .c 的文件替换成 .o

```makefile
obj = $(patsubst %.c, %.o, $(src)) # 将参数 3 中，包含参数 1 的部分，替换为参数 2。 obj = add.o sub.o mul.c div1.o
```

=======================================================================================

# v5

```makefile
src = $(wildcard *.c) # hello.c add.c sub.c mul.c  div.c

obj = $(patsubst %.c, %.o, $(src)) # hello.o add.o sub.o mul.o div.o

ALL : a.out

hello.o : hello.c
	gcc -c hello.c -o hello.o -I ./

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o

mul.o : mul.c
	gcc -c mul.c -o mul.o

div.o : div.c
	gcc -c div.c -o div.o

a.out : $(obj)
	gcc $(obj) -o a.out
```

=======================================================================================

#### clean

```makefile
-rm -rf $(obj) a.out # “-” ：作用是，删除不存在文件时，不报错。顺序执行结束。
```

每次要删除 .o 文件，很不方便，于是改写 makefile 如下：

加了clean部分

rm 前面的 - ，代表出错依然执行。比如，待删除文件集合是 5 个，已经手动删除了 1 个，就只剩下 4 个，然而删除命令里面还是 5 个的集合，就会有删除不存在文件的问题，不加这 - ，就会报错，告诉你有一个文件找不到。加了-就不会因为这个报错。

=======================================================================================

# v6

```makefile
src = $(wildcard *.c) # hello.c add.c sub.c mul.c  div.c

obj = $(patsubst %.c, %.o, $(src)) # hello.o add.o sub.o mul.o div.o

ALL : a.out

hello.o : hello.c
	gcc -c hello.c -o hello.o -I ./

add.o : add.c
	gcc -c add.c -o add.o

sub.o : sub.c
	gcc -c sub.c -o sub.o

mul.o : mul.c
	gcc -c mul.c -o mul.o

div.o : div.c
	gcc -c div.c -o div.o

a.out : $(obj)
	gcc $(obj) -o a.out 

clean :
	-rm -rf $(obj) a.out
```

### 三个自动变量和模式规则

#### 三个自动变量

```makefile
$@	# 在规则的命令中，表示规则中的目标。
$^	# 在规则的命令中，表示所有依赖条件。组成一个列表，以空格隔开，如果这个列表中有重复项，则去重
$<	# 在规则的命令中，表示第一个依赖条件。如果将该变量应用在模式规则中，它可将依赖条件列表中的依赖依次取出，套用模式规则。
```

# v7

sub， add 这些指令中使用 $< 和 $^ 都能达到效果，但是为了模式规则，所以使用的 $<

```makefile
src = $(wildcard *.c) # hello.c add.c sub.c mul.c  div.c

obj = $(patsubst %.c, %.o, $(src)) # hello.o add.o sub.o mul.o div.o

ALL : a.out

hello.o : hello.c
	gcc -c $< -o $@ -I ./

add.o : add.c
	gcc -c $< -o $@

sub.o : sub.c
	gcc -c $< -o $@

mul.o : mul.c
	gcc -c $< -o $@

div.o : div.c
	gcc -c $< -o $@

a.out : $(obj)
	gcc $^ -o $@

clean :
	-rm -rf $(obj) a.out
```

=======================================================================================

再来，**上面这个 makefile，可扩展性不行。**比如，要添加一个平方函数，就需要在 makefile 里面增加平方函数的部分。**不科学， 所以，模式规则就来了**。

##### <1>模式规则

```makefile
%.o : %.c
	gcc -c $< -o %@
```

=======================================================================================

# v8

```makefile
src = $(wildcard *.c) # hello.c add.c sub.c mul.c  div.c

obj = $(patsubst %.c, %.o, $(src)) # hello.o add.o sub.o mul.o div.o

ALL : a.out

%.o : %.c
	gcc -c $< -o $@

a.out : $(obj)
	gcc $^ -o $@

clean :
	-rm -rf $(obj) a.out
```

这时，增加一个 square 函数， 并添加 square.c 文件如下：

```c
//square.c
int suqare(int a)
{
    return a*a;
}
//head.h中加入int square(int );
//hello.c中即可直接使用
//增加函数的时候，不用改 makefile，只需要增加.c 文件，改一下源码，就行
```

##### <2>静态模式规则

继续优化 makefile，**使用静态模式规则，就是指定模式规则给谁用**，这里指定模式规则给 obj 用，以后文件多了，文件集合会有很多个，就需要指定哪个文件集合用什么规则

```makefile
$(obj) : %.o : %.c
	gcc -c $< -o %@
```

# v8.2

```c
src = $(wildcard *.c) # hello.c add.c sub.c mul.c  div.c

obj = $(patsubst %.c, %.o, $(src)) # hello.o add.o sub.o mul.o div.o

ALL : a.out

$(obj) : %.o : %.c
	gcc -c $< -o $@

a.out : $(obj)
	gcc $^ -o $@

clean :
	-rm -rf $(obj) a.out
```

### 伪目标

```
.PHONY: clean ALL
```

可以简单理解为处理clean，没有v9

# Important

将上述 .c 文件都放到 src 目录中，.h 文件都放在 inc 目录中，所生成的 .o 文件产物都放在 obj 目录中

修改 makefile 如下，主要是注意 % 的匹配理解，只匹配文件名，目录位置要手动添加

```makefile
src = $(wildcard ./src/*.c) # ./src/hello.c ./src/add.c ...

obj = $(patsubst ./src/%.c, ./obj/%.o, $(src)) # ./obj/hello.o ./obj/add.o ...

inc_path = ./inc

myArgs = -Wall -g

ALL : myName

$(obj) : ./obj/%.o : ./src/%.c
	gcc -c $< -o $@ $(myArgs) -I $(inc_path)

myName : $(obj)
	gcc $^ -o $@ $(myArgs)

clean :
	-rm -rf $(obj) myName

.PHONY : clean ALL
```

```makefile
.
├── inc
│   └── head.h
├── Makefile
├── obj
│   ├── add.o
│   ├── div.o
│   ├── hello.o
│   ├── mul.o
│   └── sub.o
├── src
│   ├── add.c
│   ├── div.c
│   ├── hello.c
│   ├── mul.c
│   └── sub.c
└── myName
```

```makefile
.
├── inc
│   └── head.h
├── Makefile
├── obj
└── src
    ├── add.c
    ├── div.c
    ├── hello.c
    ├── mul.c
    └── sub.c
```
