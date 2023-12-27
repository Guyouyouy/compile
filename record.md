```shell
#==========================
gcc -c main.c >>> main.o
gcc -c fun.c >>> fun.o
#加 -c 参数，只编译，不链接
#==========================
gcc main.c fun.c
gcc main.o fun.o
#无 -c 参数，编译与链接一块进行
#==========================
gcc -o myNmae main.c fun.c
gcc -o myName main.o fun.o
# -o 命名可执行文件名字
#==========================
```

## #include<xxx.h> 相当于声明，相当于复制粘贴过来

```c
// math_functions.c

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

```c
// main.c
#include <stdio.h>

// 引入静态库头文件
#include "math_functions.h"

int main() {
    int a = 10;
    int b = 5;

    int sum = add(a, b);
    int difference = subtract(a, b);

    printf("Sum: %d\n", sum);
    printf("Difference: %d\n", difference);

    return 0;
}
```

```c
// math_functions.h

#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

int add(int a, int b);
int subtract(int a, int b);

#endif
```

## 如果头文件不在 .c 文件同一级目录

```shell
#方式一，在头文件中使用全路径
- project
  |- main.c
  |- include
     |- myheader.h

在main.c中引用myheader.h头文件，可以按照以下方式进行操作：

#include <stdio.h>
#include "include/myheader.h"

int main() {
    // 在这里使用你的代码
    
    return 0;
}
```

```shell
#方式二
gcc -I/path/to/header main.c -o program
# -I 命令获取，头文件所在路径
```

```shell
#方式三
设置环境变量
export C_INCLUDE_PATH=/path/to/headers:/path/to/more/headers
```

```shell
#方式四
放在系统头文件目录下，可直接编译：
在CentOS系统中，系统头文件通常位于以下目录之一：gcc main.c -o program
/usr/include：这是默认的系统头文件目录，大多数系统头文件都存放在此处。
/usr/local/include：这个目录用于存放本地安装的软件包的头文件。
```

## 静态库

```shell
#继续上面的代码
gcc -c math_functions.c -o math_functions.o
ar rcs libmath.a math_functions.o
#========================================================================================
ar：这是 GNU 工具集中的一个程序，用于操作静态库（archive）。用于创建、修改和提取静态库中的对象文件。
rcs：这是 ar 命令的选项之一，指定了要执行的操作。具体含义如下：
r：将新的或更新的目标文件添加到静态库中。如果文件已经存在，则替换原有文件。
c：创建一个静态库，如果库不存在的话。如果库已经存在，这个选项不起作用。
s：创建一个索引表（symbol table），用于加快链接速度。
libmath.a：这是要创建的静态库的名称。在本例中，静态库的名称为 libmath.a。
math_functions.o：这是要添加到静态库中的目标文件的名称。在本例中，要添加的文件为 math_functions.o。
所以，这个命令的意思是将 math_functions.o 目标文件添加到名为 libmath.a 的静态库中，如果库不存在则创建。同时，还会创建一个索引表以加快链接速度。
#========================================================================================

gcc main.c -o program -L. -lmath

#如果静态库不在 .c目录
#方式一
gcc main.c -o program -L/path/to/lib -lmath
#方式二，放在系统路径下，或者如下操作
export LIBRARY_PATH=/path/to/lib:$LIBRARY_PATH
#在编译命令中不需要再指定 -L 选项 ， 编译器会自动在 LIBRARY_PATH 中搜索库文件。例如：
gcc main.c -o program -lmath
```

## 动态库

```shell
#注意与静态库建立的区别
gcc -shared -fPIC mylib.c -o libmylib.so
#注意与静态库使用的区别
gcc main.c -L. -lmylib -o main_dynamic -Wl,-rpath,.
-Wl,-rpath,. 指定的是运行时的路径，编译路径与运行路径可以不一样
```

