## Makefile的学习
### 1、自定义变量</br>
变量名 = 变量值  var=hello </br>

### 2、预定义变量</br>
AR: 归档维护程序的名称，默认值为ar</br>
CC: c编译器的名称，默认值为cc</br>
CXX: Cpp的编译器名称，默认值为g++</br>
\$@: 目标的完整名称</br>
\$<: 第一个依赖文件的名称</br>
\$^: 所有的依赖文件</br>

### 3、获取变量的值
\$(变量名)

### 4、模式匹配
 %.o:%.c</br>
    - %:通配符，匹配一个字符串</br>
    - 两个%匹配同一个字符串

### 5、函数
1、\$(wildcard PATTERN) </br>

功能：获取指定目录下指定类型的文件列表

参数：PATTERN指的是某个或多个目录下的对应的某种类型的文件，如果有多个目录，一般使用空格间隔

返回： 得到的若干个文件的文件列表，文件名之间使用空格间隔

示例： \$(wildcard *.c ./sub/*.c)
        返回值格式： a.c b.c c.c d.c

2、$(patsubst <pattern>,<replacement>,<text>)</br>
示例： \$(patsubst %.c,%.o,x.c bar.c)</br>
    返回值格式:x.o bar.o