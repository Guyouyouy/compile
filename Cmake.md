生成静态库动态库

```shell
.
├── CMakeLists.txt
└── lib
    ├── CMakeLists.txt
    ├── hello.c
    └── hello.h
    
mkdir build & cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install
#头文件和共享库安装到系统目录/usr/lib 和/usr/include/hello
```

使用静态库和动态库

```shell
.
├── CMakeLists.txt
└── src
    ├── CMakeLists.txt
    └── main.c

mkdir build & cd build
cmake 
make
./src/main	
```

